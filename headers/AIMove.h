#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"

class AIMove {
    private:
        int oldX;
        int oldY;
        int newX;
        int newY;
        // Piece* piece;


    public:
        AIMove(int _oldX, int oldY, int _newX, int _newY);

        [[nodiscard]] const int& getOldX() const { return oldX;}
        [[nodiscard]] const int& getOldY() const { return oldY;}
        [[nodiscard]] const int& getNewX() const { return newX;}
        [[nodiscard]] const int& getNewY() const { return newY;}
};

#endif
