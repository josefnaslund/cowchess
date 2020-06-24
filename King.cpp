#include "King.h"


King::King(bool color){

    alive = true;
    white = color;

    if (color){
        img = "img/king_w.png";
    }

    else {
        img = "img/king_b.png";
    }

}

