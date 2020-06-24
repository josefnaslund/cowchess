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

