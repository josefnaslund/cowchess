#ifndef KING_H
#define KING_H

#include "Board.h"
#include "Piece.h"

class King : public Piece 
{
    public:
        King(bool color, Board* _gameBoard);
        bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;
        bool controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;
};

#endif
