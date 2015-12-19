typedef struct Camera {
    struct Vec* center;
    struct Vec* position;
    struct Vec* up;
} Camera;

Camera* create_default_camera();
Camera* create_camera(double, double, double, 
        double, double, double, 
        double, double, double);
void rotate_camera_up(Camera* camera, double degrees);
void rotate_camera_left(Camera* camera, double degrees);
void zoom_camera(Camera* camera, double degrees);
