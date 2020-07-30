#include <cmath>
#include "King.h"
#include "king_w.xpm"
#include "king_b.xpm"

using std::abs, std::cout, std::endl;

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
        if (newY == oldY && b[newY][7]->isAlive() && notMoved && b[newY][7]->hasNotMoved() &&
                // and is trying to move to 'G' column
                newX == 6){

            valid = true; // try to falsify
            
            // check no pieces are in between on F-G
            for (int x = 5; x != 7; ++x){
                if (b[oldY][x]->isAlive()){
                        valid = false;
                        break;
                }
                    
            }

            if (valid){
                // check if any other piece can attack this side's sqares from E to G.

                for (int r = 0; r != 8; ++r){
                    for (int c = 0; c != 8; ++c){

                        // other piece finder
                        if (b[r][c]->isAlive() && 
                                b[r][c]->isWhite() != isWhite()){

                            // debug
                            if (b[r][c]->getType() == 'q'){
                            }

                            // can't attack columns 4, 5, 6 or 7
                            for (int k = 4; k != 7; ++k){
                                if (b[r][c]->controlsSquare(c, r, k, oldY, b, true)){
                                    valid = false;
                                    break;
                                }
                            }
                        }
                    }

                }

            }
        } // end test short castling


        //
        // test for long castling
        //
        if (newY == oldY && b[newY][0]->isAlive() && notMoved && b[newY][0]->hasNotMoved() &&
                // and is trying to move to 'C' column
                newX == 2){
            // check no pieces are in between

            valid = true;

            for (int x = 1; x != 4; ++x){
                if (b[oldY][x]->isAlive()){
                        valid = false;
                        break;
                }
                    
            }

            if (valid){
                // check if any other piece can attack this side's sqares from C to E.

                for (int r = 0; r != 8; ++r){
                    for (int c = 0; c != 8; ++c){

                        // other piece finder
                        if (b[r][c]->isAlive() && 
                                b[r][c]->isWhite() != isWhite()){

                            // can't attack columns 2, 3, 4 (C, D, E)
                            for (int k = 2; k != 5; ++k){
                                if (b[r][c]->controlsSquare(c, r, k, oldY, b, true)){
                                    valid = false;
                                    break;
                                }
                            }
                        }
                    }

                }

            }
        } // end test long castling


    }

    // test if new pos contains piece of same color
    else if (
            b[newY][newX]->isAlive() &&
            (b[oldY][oldX]->isWhite() == b[newY][newX]->isWhite())
            )
    {
        valid = false;
    }

    // test for check
    else if (testCheck && isChecked(oldX, oldY, newX, newY)){
        valid = false;
    }


    return valid;
}


bool King::controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){
    bool valid = true;

    // do not move to same pos
    if (oldX == newX && oldY == newY){
        valid = false;
    }

    // king only moves 1 step in each direction
    else if ( (abs(oldX-newX) > 1) || (abs(oldY-newY) > 1 ) ){
        valid = false;
    }

    // test for check
    else if (testCheck && isChecked(oldX, oldY, newX, newY)){
        valid = false;
    }


    return valid;
}
