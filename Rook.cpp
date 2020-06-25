#include <iostream>
#include "Rook.h"


Rook::Rook(bool color){

    alive = true;
    white = color;

    if (color){
        img = "img/rook_w.png";
    }

    else {
        img = "img/rook_b.png";
    }

}


bool Rook::validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b){
        bool valid = true;
        if ( (oldX != newX) && (oldY != newY) ){
                valid = false;
                std::cout << "Rook: BAD MOVE\n";
        }


        return valid;
}

