#include <iostream>
#include "Rook.h"
#include "rook_w.xpm"
#include "rook_b.xpm"

using std::cout;
using std::endl;

Rook::Rook(bool color, Board* _gameBoard){

    alive = true;
    white = color;
    type = 'r';
    value = 5.0;

    if (color){
        img = rook_w_xpm;
    }

    else {
        img = rook_b_xpm;
    }

    gameBoard = _gameBoard;

    notMoved = true;

}


bool Rook::validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){
    return rookValidMove(oldX, oldY, newX, newY, b, testCheck);
}

bool Rook::rookValidMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){

    bool valid = true;

    // test if new pos. is on same row or col as piece.
    if ( (oldX != newX) && (oldY != newY) ){
        valid = false;
        // std::cout << "Rook: BAD MOVE. Wrong col or row\n";
    }


    // test if new pos contains piece of same color
    if (valid){
        if ( 
                b[newY][newX]->isAlive() &&
                ( b[oldY][oldX]->isWhite() == b[newY][newX]->isWhite())
           )
        {
            valid = false;
            // std::cout << "Rook at << " << oldX << "," << oldY << ": Can't take piece of same color at " << newX << ", " << newY << "\n";
        }
    }

    // test if piece is between old and new pos.
    if (valid){
        if (oldX == newX){
            if ( newY > oldY){
                for (int i = oldY + 1; i != newY; ++i){
                    if (b[i][oldX]->isAlive()){
                        valid = false;
                        // std::cout << "Rook: BAD move. Piece in between\n";
                    }
                }

            }

            else if ( newY < oldY ){
                for (int i = oldY - 1; i != newY; --i){
                    if (b[i][oldX]->isAlive()){
                        valid = false;
                        // std::cout << "Rook: BAD move. Piece in between\n";
                    }
                }

            }

            else {
                std::cerr << "Error, should not be moved to same pos.\n";
            }


        }

        else if (newY == oldY){
            if ( newX > oldX ){
                for (int i = oldX + 1; i != newX; ++i){
                    if (b[oldY][i]->isAlive()){
                        valid = false;
                        // std::cout << "Rook: BAD move. Piece in between\n";
                    }
                }

            }

            else if (newX < oldX){
                for (int i = oldX - 1; i != newX; --i){
                    if (b[oldY][i]->isAlive()){
                        valid = false;
                        // std::cout << "Rook: BAD move. Piece in between\n";
                    }
                }

            }

            else {
                std::cerr << "Error, should not be moved to same pos\n";
            }
        }

    }

    // check for check
    if (valid && testCheck && isChecked(oldX, oldY, newX, newY)){
        // std::cout << "Rook: that will make us checked\n";
        valid = false;

    }



    return valid;
}


bool Rook::controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){
    return rookControlsSquare(oldX, oldY, newX, newY, b, testCheck);
}

bool Rook::rookControlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){

    bool valid = true;

    // don't move to same pos
    if ( oldX == newX && oldY == newY){
        valid = false;
    }

    // test if new pos. is on same row or col as piece.
    if ( (oldX != newX) && (oldY != newY) ){
        valid = false;
        // std::cout << "Rook: BAD MOVE. Wrong col or row\n";
    }

    // test if piece is between old and new pos.
    if (valid){
        if (oldX == newX){
            if ( newY > oldY){
                for (int i = oldY + 1; i != newY; ++i){
                    if (b[i][oldX]->isAlive()){
                        valid = false;
                    }
                }

            }

            else if ( newY < oldY ){
                for (int i = oldY - 1; i != newY; --i){
                    if (b[i][oldX]->isAlive()){
                        valid = false;
                    }
                }

            }

            else {
                std::cerr << "Error, should not be moved to same pos.\n";
            }


        }

        else if (newY == oldY){
            if ( newX > oldX ){
                for (int i = oldX + 1; i != newX; ++i){
                    if (b[oldY][i]->isAlive()){
                        valid = false;
                        // std::cout << "Rook: BAD move. Piece in between\n";
                    }
                }

            }

            else if (newX < oldX){
                for (int i = oldX - 1; i != newX; --i){
                    if (b[oldY][i]->isAlive()){
                        valid = false;
                        // std::cout << "Rook: BAD move. Piece in between\n";
                    }
                }

            }

            else {
                std::cerr << "Error, should not be moved to same pos\n";
            }
        }

    }

    // check for check
    if (valid && testCheck && isChecked(oldX, oldY, newX, newY)){
        // std::cout << "Rook: that will make us checked\n";
        valid = false;

    }



    return valid;
}

double Rook::getValue(){
    double val = value;
    if (notMoved){
        if (white){
            if (gameBoard->getBoard()[0][4]->getType() == 'k' &&
                    gameBoard->getBoard()[0][4]->hasNotMoved()){

                val += 0.5;
            }

        }
        else {

            if (gameBoard->getBoard()[7][4]->getType() == 'k' &&
                    gameBoard->getBoard()[7][4]->hasNotMoved()){

                val += 0.5;
            }
        }

    }
    return val;

}
