#include <cmath>
#include "King.h"
#include "img/king_w.xpm"
#include "img/king_b.xpm"


using std::abs;

King::King(bool color){

    alive = true;
    white = color;

    if (color){
        img = king_w_xpm;
    }

    else {
        img = king_b_xpm;
    }

}

bool King::validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b){
    bool valid = true;

    if ( (abs(oldX-newX) > 1) || (abs(oldY-newY) > 1 ) ){
        valid = false;
        std::cout << "King: BAD MOVE\n";
    }

    // test if new pos contains piece of same color
    if (valid){
        if (
                b[newY][newX]->isAlive() &&
                ( b[oldY][oldX]->isWhite() == b[newY][newX]->isWhite())
           )
        {
            valid = false;
            std::cout << "King: Can't take piece of same color\n";
        }
    }


    return valid;
}
