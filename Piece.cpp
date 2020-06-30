#include "Piece.h"
#include "img/piece.xpm"
#include "img/piece_w.xpm"
#include "img/piece_b.xpm"

Piece::Piece(){
    white = true;
    alive = false;
    img = piece_xpm;
}

Piece::Piece(const bool& color){

    alive = true;
    white = color;

    if (color){
        img = piece_w_xpm ;
    }

    else {
        img = piece_b_xpm;
    }

}

