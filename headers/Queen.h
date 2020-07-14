#ifndef QUEEN_H
#define QUEEN_H

#include "Board.h"
#include "Piece.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Rook, public Bishop
{
    private:
        using Rook::alive;

    public:
        Queen(bool color, Board* _gameBoard);
        bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;
        bool controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;
};

#endif
