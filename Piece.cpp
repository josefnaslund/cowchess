#include "Piece.h"

Piece::Piece(){
    white = true;
    alive = false;
    img = "img/piece.png";
}

Piece::Piece(bool color){

    alive = true;
    white = color;

    if (color){
        img = "img/piece_w.png";
    }

    else {
        img = "img/piece_b.png";
    }

}

