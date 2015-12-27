#include "camera.h"

Camera* create_default_camera() {
    return create_camera(0,0,0,
                         0,0,1,
                         0,1,0);
}

Camera* create_camera(double center_x, double center_y, double center_z,
        double camera_x, double camera_y, double camera_z,
        double up_x, double up_y, double up_z) {
    Camera* cam = malloc(sizeof(Camera));
    cam->center = create_vec(center_x, center_y, center_z, 1.0);
    cam->position = create_vec(camera_x, camera_y, camera_z, 1.0);
    cam->up = create_vec(up_x, up_y, up_z, 1.0);
}

void rotate_camera_up(Camera* cam, double degrees) {
    Vec* old_camera_pos = cam->position;
    Vec* cross = cross_vec(old_camera_pos, cam->up);
    Vec* u_hat = normalize_vec(cross);

    Vec* new_position = rotate_vec(old_camera_pos, u_hat, degrees);
    Vec* normalized = normalize_vec(new_position);

    if (normalized->y < 0.2 || normalized->y > 0.95) {
        delete_vec(normalized);
        delete_vec(new_position);
        delete_vec(cross);
        delete_vec(u_hat);
        return;
    }
    cam->position = new_position;

    delete_vec(normalized);
    delete_vec(old_camera_pos);
    delete_vec(cross);
    delete_vec(u_hat);
}

void rotate_camera_left(Camera* cam, double degrees) {
    Vec* old_camera_pos = cam->position;
    Vec* up_hat = normalize_vec(cam->up);

    cam->position = rotate_vec(old_camera_pos, up_hat, degrees);

    delete_vec(old_camera_pos);
    delete_vec(up_hat);
}

void zoom_camera(Camera* cam, double zoom) {
    Vec* old_camera_pos = cam->position;

    cam->position = scale_vec(old_camera_pos, zoom);

    delete_vec(old_camera_pos);
}
