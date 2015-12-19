#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "gl_utils.h"
#include "camera.h"
#include "maths.h"
#include "mesh_import.h"

static Mat* convert_assimp_matrix(struct aiMatrix4x4 m) {
    return create_mat(
            1.0, 0.0, 0.0, m.a4,
            0.0, 1.0, 0.0, m.b4,
            0.0, 0.0, 1.0, m.c4,
            0.0, 0.0, 0.0, m.d4);
}

int import_skeleton_node(struct aiNode* assimp_node, 
        Skeleton_Node** skeleton_node,
        int bone_count,
        char bone_names[][64]) {
    Skeleton_Node* temp = malloc(sizeof(Skeleton_Node)); 

    gl_log(INFO, "Creating node %s", assimp_node->mName.data);
    gl_log(INFO, "Node has %d children", assimp_node->mNumChildren);

    strcpy(temp->name, assimp_node->mName.data);
    temp->num_children = 0;
    temp->bone_index = -1;

    for (int i = 0; i < 64; i++) {
        temp->children[i] = 0;
    }

    int has_bone = 0;
    for (int i = 0; i < bone_count; i++) {
        if (strcmp(bone_names[i], temp->name)) {
            gl_log(INFO, "Node uses bone %d", i);
            temp->bone_index = i;
            has_bone = 1;
            break;
        }
    }
    if (!has_bone) {
        gl_log(INFO, "No bones for node");
    }

    int has_useful_child = 0;
    for (int i = 0; i < assimp_node->mNumChildren; i++) {
        int result = import_skeleton_node(
                assimp_node->mChildren[i],
                &temp->children[temp->num_children],
                bone_count,
                bone_names);
        if (result) {
            has_useful_child = 1;
            temp->num_children++;
        } else {
            gl_log(INFO, "Culled useless node");
        }
    }
    gl_log(INFO, "Finished node %s", assimp_node->mName.data);
    if (has_useful_child || has_bone) {
        *skeleton_node = temp;
        return 1;
    }
    return 0;
}

int load_mesh(
        const char* filename, 
        GLuint* vao,
        int* point_count, 
        Skeleton_Node** root_node,
        Mat* bone_offset_mats[]) 
{
    const struct aiScene* scene = aiImportFile(filename, aiProcess_Triangulate);
    if (!scene) {
        gl_log(ERROR, "Cannot open mesh file: %s", filename);
        return 0;
    }

    gl_log(INFO, "Loading mesh: %s", filename);
    gl_log(INFO, "%d animations", scene->mNumAnimations);
    gl_log(INFO, "%d cameras", scene->mNumCameras);
    gl_log(INFO, "%d lights", scene->mNumLights);
    gl_log(INFO, "%d materials", scene->mNumMaterials);
    gl_log(INFO, "%d meshes", scene->mNumMeshes);
    gl_log(INFO, "%d textures", scene->mNumTextures);

    const struct aiMesh* mesh = scene->mMeshes[0];
    gl_log(INFO, "%d vertices", mesh->mNumVertices);

    *point_count = mesh->mNumVertices;

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    GLfloat* points;
    GLfloat* normals;
    GLint* bone_ids;

    // If has vertices
    if (mesh->mVertices && mesh->mNumVertices > 0)	{
        points = (GLfloat*) malloc(*point_count * 3 * sizeof(GLfloat));
        for	(int i = 0; i < *point_count; i++)	{
            const struct aiVector3D* vp = &(mesh->mVertices[i]);
            points[i * 3] = (GLfloat)vp->x;
            points[i * 3 + 1] = (GLfloat)vp->y;
            points[i * 3 + 2] = (GLfloat)vp->z;
        }

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                3 * *point_count * sizeof (GLfloat),
                points,
                GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);
    }

    // If has normals
    if (mesh->mNormals) {
        normals = (GLfloat*) malloc(*point_count * 3 * sizeof(GLfloat));
        for (int i = 0; i < *point_count; i++) {
            const struct aiVector3D* vn = &(mesh->mNormals[i]);
            normals[i * 3] = (GLfloat)vn->x;
            normals[i * 3 + 1] = (GLfloat)vn->y;
            normals[i * 3 + 2] = (GLfloat)vn->z;
        }

		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER,
			3 * *point_count * sizeof (GLfloat),
			normals,
			GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
    }

    // If has bones
    if (mesh->mBones && mesh->mNumBones > 0) {
        int bone_count = (int) mesh->mNumBones;
        char bone_names[256][64];
        bone_ids = (GLint*) malloc(*point_count * sizeof(GLint));
        gl_log(INFO, "%d bones", bone_count);

        for	(int b_i = 0; b_i < bone_count; b_i++)	{
            const struct aiBone* bone = mesh->mBones[b_i];
            strcpy(bone_names[b_i], bone->mName.data);

            bone_offset_mats[b_i] = convert_assimp_matrix(bone->mOffsetMatrix);

            gl_log(INFO, "Bone name %d = %s", b_i, bone_names[b_i]);

            int num_weights = bone->mNumWeights;
            for (int w_i = 0; w_i < num_weights; w_i++) {
                struct aiVertexWeight weight = bone->mWeights[w_i];
                int vertex_id = weight.mVertexId;

                if (weight.mWeight >= 0.5) {
                    bone_ids[vertex_id] = b_i;
                }
            }
        }

        struct aiNode* assimp_node = scene->mRootNode;
        
        import_skeleton_node(assimp_node, root_node, bone_count, bone_names);

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                *point_count * sizeof (GLint),
                bone_ids,
                GL_STATIC_DRAW);
        glVertexAttribIPointer(2, 1, GL_INT, 0, NULL);
        glEnableVertexAttribArray(2);
    }

    aiReleaseImport(scene);
    gl_log(INFO, "Finished loading mesh: %s", filename);

    return 1;
}
