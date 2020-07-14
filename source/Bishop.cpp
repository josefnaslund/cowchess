#include <iostream>
#include <cmath>
#include "Bishop.h"
#include "bishop_w.xpm"
#include "bishop_b.xpm"

using std::cout;
using std::endl;
using std::abs;

Bishop::Bishop(bool color, Board* _gameBoard){

    alive = true;
    white = color;
    type = 'r';
    value = 3.0;

    if (color){
        img = bishop_w_xpm;
    }

    else {
        img = bishop_b_xpm;
    }

    gameBoard = _gameBoard;

    notMoved = true;

}


bool Bishop::validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){
    return bishopValidMove(oldX, oldY, newX, newY, b, testCheck);
}

bool Bishop::bishopValidMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){

    bool valid = false;

    // don't move to same pos.
    if (!(oldX == newX || oldY == newY)){

        // don't move to piece of same color
        if ((!b[newY][newX]->isAlive()) || (white != b[newY][newX]->isWhite())){

            // moves should be in square
            if (abs(oldX - newX) == abs(oldY - newY)){
                valid = true;

                // check pieces in between
                // every direction is possible - bishops can move in 4 directions
                int x = oldX, y = oldY;

                // check every square for obstacles until final position
                while (abs(x - newX) != 1){

                    if (newX > x)
                        ++x;
                    else
                        --x;

                    if (newY > y)
                        ++y;
                    else
                        --y;

                    if (b[y][x]->isAlive()){
                        valid = false;
                        break;
                    }
                }
            }
        }
    }

    // check for check
    if (valid && testCheck && isChecked(oldX, oldY, newX, newY)){
        valid = false;
    }

    return valid;
}


bool Bishop::controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){
    return bishopControlsSquare(oldX, oldY, newX, newY, b, testCheck);
}

bool Bishop::bishopControlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){

    bool valid = false;

    // don't move to same pos.
    if (!(oldX == newX || oldY == newY)){

        // moves should be in square
        if (abs(oldX - newX) == abs(oldY - newY)){
            valid = true;

            // check pieces in between
            // every direction is possible - bishops can move in 4 directions
            int x = oldX, y = oldY;

            // check every square for obstacles until final position
            while (abs(x - newX) != 1){

                if (newX > x)
                    ++x;
                else
                    --x;

                if (newY > y)
                    ++y;
                else
                    --y;

                if (b[y][x]->isAlive()){
                    valid = false;
                    break;
                }
            }
        }
    }

    // check for check
    if (valid && testCheck && isChecked(oldX, oldY, newX, newY)){
        valid = false;
    }

    return valid;
}
