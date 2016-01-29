#ifndef BILLIARDS_BILLIARDSPOCKET_H
#define BILLIARDS_BILLIARDSPOCKET_H

class BilliardsPocket {
public:
    CircleBoundingObject boundingCircle;

    BilliardsPocket(CircleBoundingObject boundingCircle)
            : boundingCircle{boundingCircle} { }
};

#endif //BILLIARDS_BILLIARDSPOCKET_H
