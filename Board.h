#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

class Board{
    private:
        Piece** board;
        int moveCount;

    public:
        Board();
        Piece** getBoard() {return board;}
        Piece* getPieceAt(int arrX, int arrY);
        bool movePiece(int oldX, int oldY, int newX, int newY);
        

};

#endif
