#ifndef ROOK_H
#define ROOK_H

#include "Board.h"
#include "Piece.h"


class Rook : public Piece 
{
    public:
        Rook(bool color, Board* _gameBoard);
        bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;
};

#endif
