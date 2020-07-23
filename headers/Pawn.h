#ifndef PAWN_H
#define PAWN_H

#include "Board.h"
#include "Piece.h"

class Pawn : public Piece 
{
    public:
        Pawn(bool color, Board* _gameBoard);
        bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;
        bool controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;
        double getValue() override;
};

#endif
