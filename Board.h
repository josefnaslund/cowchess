#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

class Board{
    private:
        Piece** board;

    public:
        Board();
        Piece** getBoard() {return board;}
};

#endif
