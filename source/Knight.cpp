#include <cmath>
#include "Knight.h"
#include "knight_w.xpm"
#include "knight_b.xpm"


using std::abs;
using std::cout;
using std::endl;

Knight::Knight(bool color, Board* _gameBoard){

    alive = true;
    white = color;
    type = 'n';
    value = 3;


    if (color){
        img = knight_w_xpm;
    }

    else {
        img = knight_b_xpm;
    }

    gameBoard = _gameBoard;

    notMoved = true;

}

bool Knight::validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){
    bool valid = false;

    if (abs(oldX - newX) == 2 && abs(oldY - newY) == 1 && ((isWhite() != b[newY][newX]->isWhite()) || !b[newY][newX]->isAlive())){
        valid = true;
    }

    else if (abs(oldX - newX) == 1 && abs(oldY - newY) == 2 && ((isWhite() != b[newY][newX]->isWhite()) || !b[newY][newX]->isAlive())){
        valid = true;
    }

    if (testCheck && valid && isChecked(oldX, oldY, newX, newY)){
        valid = false;
            
    }

    return valid;
}


bool Knight::controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) { 
    bool valid = false;

    if (abs(oldX - newX) == 2 && abs(oldY - newY) == 1 ){
        valid = true;
    }

    else if (abs(oldX - newX) == 1 && abs(oldY - newY) == 2){
        valid = true;
    }

    if (testCheck && valid && isChecked(oldX, oldY, newX, newY)){
        valid = false;
            
    }

    return valid;
}
