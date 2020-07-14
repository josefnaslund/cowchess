#include <cmath>
#include "King.h"
#include "king_w.xpm"
#include "king_b.xpm"


using std::abs;
using std::cout;
using std::endl;

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

    notMoved = true;

}

bool King::validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){
    bool valid = true;

    // do not move to same pos
    if (oldX == newX && oldY == newY){
        // std::cout << "King: Can't move to same pos\n";
        valid = false;
    }




    // king only moves 1 step in each direction, except for castling
    else if ( (abs(oldX-newX) > 1) || (abs(oldY-newY) > 1 ) ){
        valid = false;
        
        //
        // short castling
        // first check that neither piece have moved

        if (newY == oldY && notMoved && b[newY][7]->hasNotMoved() &&
                // and is trying to move to 'G' column
                newX == 6){

            // check no pieces are in between

            valid = true;

            for (int x = 5; x != 7; ++x){
                if (b[oldY][x]->isAlive()){
                        valid = false;
                        break;
                }
                    
            }

            if (valid){
                // check if any other piece can attack this side's sqares from E to H.

                for (int r = 0; r != 7; ++r){
                    for (int c = 0; c != 7; ++c){

                        // other piece finder
                        if (b[r][c]->isAlive() && 
                                b[r][c]->isWhite() != isWhite()){

                            // can't attack columns 4, 5, 6 or 7
                            for (int k = 4; k != 8; ++k){
                                if (b[r][c]->controlsSquare(c, r, k, oldY, b, 1)){
                                    valid = false;
                                    break;
                                }
                            }
                        }
                    }

                }

            }
        } // end test short castling

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
