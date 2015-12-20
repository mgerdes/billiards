typedef struct BilliardsTable {
    Model* model;
} BilliardsTable;

typedef struct BilliardsBall {
    Model* model;
    Vec* position;
    Vec* velocity;
    double theta;
} BilliardsBall;

typedef struct CueBallArrow {
    Model* model;
    double theta;
    double magnitude;
} CueBallArrow;

typedef struct BilliardsGame {
    double last_draw_time;
    BilliardsTable* table;
    BilliardsBall** balls;
    CueBallArrow* cue_ball_arrow;
} BilliardsGame;

BilliardsGame* create_billiards_game(GLint shader_program);
void draw_billiards_game(BilliardsGame* billiards_game);
void hit_cue_ball(BilliardsGame* game);
