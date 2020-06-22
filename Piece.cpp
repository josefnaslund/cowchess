#include "Piece.h"

Piece::Piece(){
    white = true;
    alive = false;
    img = "img/piece.png";
}

Piece::Piece(bool white){

        alive = true;

        if (white){
            white = true;
            img = "img/piece_w.png";
            alive = true;
        }

        else {
                white = false;
                img = "img/piece_b.png";
                alive = true;
        }
        
}
