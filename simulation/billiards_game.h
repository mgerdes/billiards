typedef struct BilliardsTable {
    Model* model;
} BilliardsTable;

typedef struct BilliardsBall {
    Model* model;
    Vec* position;
    Vec* velocity;
    double theta;
} BilliardsBall;

typedef struct BilliardsGame {
    BilliardsTable* table;
    BilliardsBall** balls;
} BilliardsGame;

BilliardsGame* create_billiards_game(GLint shader_program);
void draw_billiards_game(BilliardsGame* billiards_game);
