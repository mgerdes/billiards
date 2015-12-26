typedef struct BilliardsTable {
    Model* model;
} BilliardsTable;

typedef struct BilliardsBall {
    Model* model;
    Vec* position;
    Vec* velocity;
    double theta;
    int is_in_hole;
} BilliardsBall;

typedef struct CueStick {
    Model* model;
    double theta;
    double hit_magnitude;
} CueStick;

typedef struct BilliardsGame {
    double last_draw_time;
    BilliardsTable* table;
    BilliardsBall** balls;
    CueStick* cue_stick;
} BilliardsGame;

BilliardsGame* create_billiards_game(GLint shader_program);
void draw_billiards_game(BilliardsGame* billiards_game);
void hit_cue_ball(BilliardsGame* game);
void increase_hit_magnitude(BilliardsGame* game);
void decrease_hit_magnitude(BilliardsGame* game);
