#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "camera.h"
#include "maths.h"
#include "mesh.h"
#include "model.h"
#include "billiards_game.h"

#define NUM_BALLS 4

BilliardsGame* create_billiards_game(GLint shader_program) {
    BilliardsGame* billiards_game = malloc(sizeof(BilliardsGame));

    billiards_game->table = malloc(sizeof(BilliardsTable));
    billiards_game->balls = malloc(sizeof(BilliardsBall*) * NUM_BALLS);
    for (int i = 0; i < NUM_BALLS; i++) {
        billiards_game->balls[i] = malloc(sizeof(BilliardsBall));
    }

    billiards_game->table->model = create_model("objects/models/table.obj", shader_program);

    billiards_game->balls[0]->model = create_model("objects/models/ball_1.obj", shader_program);
    billiards_game->balls[0]->position = create_vec(0.0, 0.28, 0.0, 0.0);
    billiards_game->balls[0]->velocity = create_vec(0.005, 0.0, 0.005, 0.0);
    billiards_game->balls[0]->theta = 0.0;

    billiards_game->balls[1]->model = create_model("objects/models/ball_2.obj", shader_program);
    billiards_game->balls[1]->position = create_vec(0.2, 0.28, 0.0, 0.0);
    billiards_game->balls[1]->velocity = create_vec(0.005, 0.0, 0.009, 0.0);
    billiards_game->balls[1]->theta = 0.0;

    billiards_game->balls[2]->model = create_model("objects/models/ball_3.obj", shader_program);
    billiards_game->balls[2]->position = create_vec(0.0, 0.28, 0.0, 0.0);
    billiards_game->balls[2]->velocity = create_vec(0.009, 0.0, 0.005, 0.0);
    billiards_game->balls[2]->theta = 0.0;

    billiards_game->balls[3]->model = create_model("objects/models/ball_4.obj", shader_program);
    billiards_game->balls[3]->position = create_vec(0.2, 0.28, 0.0, 0.0);
    billiards_game->balls[3]->velocity = create_vec(0.002, 0.0, 0.009, 0.0);
    billiards_game->balls[3]->theta = 0.0;

    return billiards_game;
}

static void move_ball(BilliardsBall* ball) {
    Vec* velocity = ball->velocity;
    Vec* old_position = ball->position;
    ball->position = create_vec(old_position->x + velocity->x,
                                old_position->y + velocity->y,
                                old_position->z + velocity->z, 0);
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

        if (fabs(x - x_o) < 0.03 &&
            fabs(y - y_o) < 0.03 &&
            fabs(z - z_o) < 0.03) {
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

            Vec* v1_p = vec_minus_vec(v1, temp13);
            Vec* v2_p = vec_minus_vec(v2, temp23);

            ball->velocity = v1_p;
            other_ball->velocity = v2_p;
        }

    }
}

static void handle_collisions_for_ball(BilliardsGame* game, BilliardsBall* ball) {
    handle_collision_for_ball_with_edge(ball);
    handle_collision_for_ball_with_other_balls(game, ball);
}

static Mat* set_model_mat_for_ball(BilliardsBall* ball) {
    Vec* rotation_vec = cross_vec(normalize_vec(ball->velocity), &y_axis);
    Mat* rotation_mat = create_rotation_mat(rotation_vec, ball->theta += 0.15);
    Mat* translation_mat = create_translation_mat(ball->position->x, ball->position->y, ball->position->z);
    ball->model->model_mat = mat_times_mat(translation_mat, rotation_mat);
}

static void draw_balls(BilliardsGame* game) {
    for (int i = 0; i < NUM_BALLS; i++) {
        BilliardsBall* ball = game->balls[i];

        move_ball(ball);
        handle_collisions_for_ball(game, ball);
        set_model_mat_for_ball(ball);

        draw_model(ball->model);
    }
}

static void draw_table(BilliardsGame* billiards_game) {
    draw_model(billiards_game->table->model);
}

void draw_billiards_game(BilliardsGame* billiards_game) {
    draw_balls(billiards_game);
    draw_table(billiards_game);
}
