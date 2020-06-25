#include <cmath>
#include "King.h"

using std::abs;

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

bool King::validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b){
        bool valid = true;

        if ( (abs(oldX-newX) > 1) || (abs(oldY-newY) > 1 ) ){
                valid = false;
                std::cout << "King: BAD MOVE\n";
        }


        return valid;
}
