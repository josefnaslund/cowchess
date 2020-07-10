#include <cmath>
#include "King.h"
#include "king_w.xpm"
#include "king_b.xpm"


using std::abs;

King::King(bool color, Board* _gameBoard){

    alive = true;
    white = color;
    type = 'k';
    value = 99.9;


    if (color){
        img = king_w_xpm;
    }

    else {
        img = king_b_xpm;
    }

    gameBoard = _gameBoard;

}

bool King::validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){
    bool valid = true;

    // do not move to same pos
    if (oldX == newX && oldY == newY){
        // std::cout << "King: Can't move to same pos\n";
        valid = false;
    }


    // king only moves 1 step in each direction
    else if ( (abs(oldX-newX) > 1) || (abs(oldY-newY) > 1 ) ){
        valid = false;
        // std::cout << "King: BAD MOVE\n";
    }

    // test if new pos contains piece of same color
    else if (
            b[newY][newX]->isAlive() &&
            (b[oldY][oldX]->isWhite() == b[newY][newX]->isWhite())
            )
    {
        valid = false;
        // std::cout << "King: Can't take piece of same color\n";
    }

    // test for check
    else if (testCheck && isChecked(oldX, oldY, newX, newY)){
        // std::cout << "King is checked\n";
        valid = false;
    }


    return valid;
}


bool King::controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){
    bool valid = true;

    // do not move to same pos
    if (oldX == newX && oldY == newY){
        // std::cout << "King: Can't move to same pos\n";
        valid = false;
    }


    // king only moves 1 step in each direction
    else if ( (abs(oldX-newX) > 1) || (abs(oldY-newY) > 1 ) ){
        valid = false;
        // std::cout << "King: BAD MOVE\n";
    }


    // test for check
    else if (testCheck && isChecked(oldX, oldY, newX, newY)){
        // std::cout << "King is checked\n";
        valid = false;
    }


    return valid;
}
