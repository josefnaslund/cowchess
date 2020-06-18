#include "Piece.h"

Piece::Piece(){
    white = true;
    exist = false;
    img = "img/piece.png";
}

Piece::Piece(bool white){

        exist = true;

        if (white){
            white = true;
            img = "img/piece.png";
            exist = true;
        }

        else {
                white = false;
                img = "img/piece.png";
                exist = true;
        }
        
}
