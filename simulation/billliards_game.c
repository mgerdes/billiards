#include "billiards_game.h"

#define NUM_BALLS 9
#define EPSILON 0.001
#define MAX_HIT_MAGNITUDE 1.0
#define MIN_HIT_MAGNITUDE 0.1

double hole_delta = 0.010;

double holes[] = {
    -0.299, -0.179,
    -0.299,  0.179,
     0.599, -0.179,
     0.599,  0.179,
     0.15,   -0.179,
     0.15,    0.179
};

BilliardsGame* create_billiards_game(GLint shader_program) {
    BilliardsGame* game = malloc(sizeof(BilliardsGame));

    game->table = malloc(sizeof(BilliardsTable));
    game->balls = malloc(sizeof(BilliardsBall*) * NUM_BALLS);
    for (int i = 0; i < NUM_BALLS; i++) {
        game->balls[i] = malloc(sizeof(BilliardsBall));
    }
    game->cue_stick = malloc(sizeof(CueStick));

    game->table->model = create_model("objects/models/table.obj", shader_program);

    game->balls[0]->model = create_model("objects/models/cue_ball.obj", shader_program);
    game->balls[0]->position = create_vec(-0.20, 0.28, -0.12, 0.0);
    game->balls[0]->velocity = create_vec(0.01, 0.0, 0.0, 0.0);
    game->balls[0]->theta = 0.0;
    game->balls[0]->is_in_hole = 0;

    game->balls[1]->model = create_model("objects/models/ball_1.obj", shader_program);
    game->balls[1]->position = create_vec(-0.20, 0.28, 0.0, 0.0);
    game->balls[1]->velocity = create_vec(0.2, 0.0, 0.2, 0.0);
    game->balls[1]->theta = 0.0;
    game->balls[1]->is_in_hole = 0;

    game->balls[2]->model = create_model("objects/models/ball_2.obj", shader_program);
    game->balls[2]->position = create_vec(-0.10, 0.28, 0.0, 0.0);
    game->balls[2]->velocity = create_vec(0.5, 0.0, 0.4, 0.0);
    game->balls[2]->theta = 0.0;
    game->balls[2]->is_in_hole = 0;

    game->balls[3]->model = create_model("objects/models/ball_3.obj", shader_program);
    game->balls[3]->position = create_vec(0.00, 0.28, 0.1, 0.0);
    game->balls[3]->velocity = create_vec(0.0, 0.0, 0.4, 0.0);
    game->balls[3]->theta = 0.0;
    game->balls[3]->is_in_hole = 0;

    game->balls[4]->model = create_model("objects/models/ball_4.obj", shader_program);
    game->balls[4]->position = create_vec(0.10, 0.28, 0.0, 0.0);
    game->balls[4]->velocity = create_vec(0.2, 0.0, 0.2, 0.0);
    game->balls[4]->theta = 0.0;
    game->balls[4]->is_in_hole = 0;

    game->balls[5]->model = create_model("objects/models/ball_5.obj", shader_program);
    game->balls[5]->position = create_vec(0.20, 0.28, 0.0, 0.0);
    game->balls[5]->velocity = create_vec(0.2, 0.0, 0.3, 0.0);
    game->balls[5]->theta = 0.0;
    game->balls[5]->is_in_hole = 0;

    game->balls[6]->model = create_model("objects/models/ball_6.obj", shader_program);
    game->balls[6]->position = create_vec(0.30, 0.28, 0.0, 0.0);
    game->balls[6]->velocity = create_vec(0.2, 0.0, 0.1, 0.0);
    game->balls[6]->theta = 0.0;
    game->balls[6]->is_in_hole = 0;

    game->balls[7]->model = create_model("objects/models/ball_7.obj", shader_program);
    game->balls[7]->position = create_vec(0.40, 0.28, 0.0, 0.0);
    game->balls[7]->velocity = create_vec(0.2, 0.0, 0.3, 0.0);
    game->balls[7]->theta = 0.0;
    game->balls[7]->is_in_hole = 0;

    game->balls[8]->model = create_model("objects/models/ball_8.obj", shader_program);
    game->balls[8]->position = create_vec(0.50, 0.28, 0.0, 0.0);
    game->balls[8]->velocity = create_vec(0.2, 0.0, 0.2, 0.0);
    game->balls[8]->theta = 0.0;
    game->balls[8]->is_in_hole = 0;

    game->cue_stick->model = create_model("objects/models/cue.obj", shader_program);
    game->cue_stick->theta = 0.0;
    game->cue_stick->hit_magnitude = 0.5;

    game->last_draw_time = glfwGetTime();

    return game;
}

static void handle_collision_for_ball_with_edge(BilliardsBall* ball) {
    if (ball->position->x > 0.6) {
        ball->position->x = 0.599;
        ball->velocity->x *= -1;
    }
    if (ball->position->x < -0.3) {
        ball->position->x = -0.299;
        ball->velocity->x *= -1;
    }
    if (ball->position->z > 0.18) {
        ball->position->z = 0.179;
        ball->velocity->z *= -1;
    }
    if (ball->position->z < -0.18) {
        ball->position->z = -0.179;
        ball->velocity->z *= -1;
    }
}

static void handle_collision_for_ball_with_other_balls(BilliardsGame* game, BilliardsBall* ball) {
    for (int i = 0; i < NUM_BALLS; i++) {
        BilliardsBall* other_ball = game->balls[i];
        if (other_ball == ball) continue;

        double x = ball->position->x;
        double y = ball->position->y;
        double z = ball->position->z;

        double x_o = other_ball->position->x;
        double y_o = other_ball->position->y;
        double z_o = other_ball->position->z;

        double distance = sqrt((x-x_o)*(x-x_o) + (y-y_o)*(y-y_o) + (z-z_o)*(z-z_o));

        double radius = 0.03613;

        if (distance < radius) {
            Vec* x1 = create_vec(x,y,z,0);
            Vec* x2 = create_vec(x_o,y_o,z_o,0);
            Vec* v1 =  ball->velocity;
            Vec* v2 =  other_ball->velocity;

            Vec* temp11 = vec_minus_vec(x1, x2);
            Vec* temp12 = vec_minus_vec(v1, v2);
            double divisor1 = dot_vec(temp11, temp11);
            double scale_temp1 = dot_vec(temp11, temp12) / divisor1;
            Vec* temp13 = scale_vec(temp11, scale_temp1);

            Vec* temp21 = vec_minus_vec(x2, x1);
            Vec* temp22 = vec_minus_vec(v2, v1);
            double divisor2 = dot_vec(temp21, temp21);
            double scale_temp2 = dot_vec(temp21, temp22) / divisor2;
            Vec* temp23 = scale_vec(temp21, scale_temp2);

            ball->velocity = vec_minus_vec(v1, temp13);
            other_ball->velocity = vec_minus_vec(v2, temp23);
        }
    }
}

static void handle_collisions_for_ball(BilliardsGame* game, BilliardsBall* ball) {
    handle_collision_for_ball_with_edge(ball);
    handle_collision_for_ball_with_other_balls(game, ball);
}

static Mat* set_model_mat_for_ball(BilliardsBall* ball) {
    Vec* rotation_vec = cross_vec(normalize_vec(ball->velocity), &y_axis);
    Mat* rotation_mat;
    if (dot_vec(ball->velocity, ball->velocity) > 0) {
        rotation_mat = create_rotation_mat(rotation_vec, ball->theta);
    } else {
        rotation_mat = identity_mat();
    }
    Mat* translation_mat = create_translation_mat(ball->position->x, ball->position->y, ball->position->z);
    ball->model->model_mat = mat_times_mat(translation_mat, rotation_mat);
}

static void move_ball(BilliardsBall* ball, double elapsed_time) {
    Vec* velocity = ball->velocity;
    if (sqrt(dot_vec(velocity, velocity)) > EPSILON) {
        Vec* position = ball->position;
        Vec* acceleration = scale_vec(normalize_vec(velocity), -0.1);

        ball->velocity = vec_plus_vec(velocity, scale_vec(acceleration, elapsed_time));
        ball->position = vec_plus_vec(position, scale_vec(vec_plus_vec(velocity, ball->velocity), elapsed_time / 2.0));

        ball->theta += sqrt(dot_vec(ball->velocity, ball->velocity)) * elapsed_time * 20;
    }
}

static void handle_ball_in_pocket(BilliardsBall* ball) {
    for (int i = 0; i < 6; i++) {
        double hole_x = holes[i*2];
        double hole_z = holes[i*2+1];

        double ball_x = ball->position->x;
        double ball_z = ball->position->z;

        double dist = sqrt((hole_x - ball_x)*(hole_x - ball_x)
                           + (hole_z - ball_z)*(hole_z - ball_z));

        if (dist <= hole_delta) {
            ball->is_in_hole = 1;
            ball->velocity = create_vec(0, 0, 0, 1);
            ball->position = create_vec(1, 1, 1, 1);
        }
    }
}

static void draw_balls(BilliardsGame* game, double elapsed_time) {
    for (int i = 0; i < NUM_BALLS; i++) {
        BilliardsBall *ball = game->balls[i];

        if (ball->is_in_hole) {
            if (i == 0) {
                ball->is_in_hole = 0;
                game->balls[0]->position = create_vec(-0.20, 0.28, -0.12, 0.0);
            }
            continue;
        }

        handle_ball_in_pocket(ball);
        move_ball(ball, elapsed_time);
        handle_collisions_for_ball(game, ball);
        set_model_mat_for_ball(ball);

        draw_model(ball->model);
    }
}

static void draw_table(BilliardsGame* game) {
    draw_model(game->table->model);
}

static void draw_cue_stick(BilliardsGame* game) {
    CueStick* cue_stick = game->cue_stick;
    BilliardsBall* cue_ball = game->balls[0];
    Mat* scale = create_scale_mat(0.4, 0.4, 0.4);
    Mat* rotate_sideways = create_rotation_mat(&x_axis, M_PI / 2.0);
    double offset =  0.33 + (0.08 / 0.9) * (cue_stick->hit_magnitude - 0.1);
    Mat* move_outside_sphere = create_translation_mat(-offset, 0, 0.0);
    Mat* rotate_around_sphere = create_rotation_mat(&y_axis, cue_stick->theta - (M_PI / 2.0));
    Mat* move_to_sphere = create_translation_mat(cue_ball->position->x, cue_ball->position->y, cue_ball->position->z);

    cue_stick->model->model_mat = mat_times_mat(move_to_sphere,
                                                     mat_times_mat(mat_times_mat(rotate_around_sphere,
                                                                                 move_outside_sphere),
                                                                   mat_times_mat(rotate_sideways,
                                                                                 scale)));
    draw_model(cue_stick->model);
}

static int no_balls_moving(BilliardsGame* game) {
    for (int i = 0; i < NUM_BALLS; i++) {
        BilliardsBall* ball = game->balls[i];
        double speed_sqrd = dot_vec(ball->velocity, ball->velocity);
        if (speed_sqrd > EPSILON) {
            return 0;
        }
    }
    return 1;
}

void hit_cue_ball(BilliardsGame* game) {
    game->balls[0]->velocity = rotate_vec_y(create_vec(0.0, 0.0, -1.0 * game->cue_stick->hit_magnitude, 0.0),
                                            game->cue_stick->theta);
    game->cue_stick->hit_magnitude = 0.50;
}

void increase_hit_magnitude(BilliardsGame* game) {
    game->cue_stick->hit_magnitude += 0.006;
    if (game->cue_stick->hit_magnitude > MAX_HIT_MAGNITUDE) {
        game->cue_stick->hit_magnitude = MAX_HIT_MAGNITUDE;
    }
}

void decrease_hit_magnitude(BilliardsGame* game) {
    game->cue_stick->hit_magnitude -= 0.006;
    if (game->cue_stick->hit_magnitude < MIN_HIT_MAGNITUDE) {
        game->cue_stick->hit_magnitude = MIN_HIT_MAGNITUDE;
    }
}

void draw_billiards_game(BilliardsGame* game) {
    double current_time = glfwGetTime();
    double elapsed_time = current_time - game->last_draw_time;
    game->last_draw_time = current_time;
    draw_balls(game, elapsed_time);
    draw_table(game);
    if (no_balls_moving(game)) {
        draw_cue_stick(game);
    }
}
