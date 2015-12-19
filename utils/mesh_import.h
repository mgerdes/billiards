typedef struct Skeleton_Node {
    struct Skeleton_Node* children[64];
    char name[64];
    int num_children;
    int bone_index;
} Skeleton_Node;

int load_mesh(const char* filename, GLuint* vao, int* point_count, Skeleton_Node**, Mat* bone_offset_mats[]);
