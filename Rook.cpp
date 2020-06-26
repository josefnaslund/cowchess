#include <iostream>
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


bool Rook::validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b){
    bool valid = true;

    // test if new pos. is on same row or col as piece.
    if ( (oldX != newX) && (oldY != newY) ){
        valid = false;
        std::cout << "Rook: BAD MOVE\n";
    }


    // test if new pos contains piece of same color
    if (valid){
        if ( 
                b[newY][newX]->isAlive() &&
                ( b[oldY][oldX]->isWhite() == b[newY][newX]->isWhite())
           )
        {
            valid = false;
            std::cout << "Rook: Can't take piece of same color\n";
        }
    }

    // test if piece is between old and new pos.
    if (valid){
        if (oldX == newX){
            if ( newY > oldY){
                for (int i = oldY + 1; i != newY; ++i){
                    if (b[i][oldX]->isAlive()){
                        valid = false;
                        std::cout << "Rook: BAD move. Piece in between\n";
                    }
                }

            }

            else if ( newY < oldY ){
                for (int i = oldY - 1; i != newY; --i){
                    if (b[i][oldX]->isAlive()){
                        valid = false;
                        std::cout << "Rook: BAD move. Piece in between\n";
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
                        std::cout << "Rook: BAD move. Piece in between\n";
                    }
                }

            }

            else if (newX < oldX){
                for (int i = oldX - 1; i != newX; --i){
                    if (b[oldY][i]->isAlive()){
                        valid = false;
                        std::cout << "Rook: BAD move. Piece in between\n";
                    }
                }

            }

            else {
                std::cerr << "Error, should not be moved to same pos\n";
            }
        }

    }


    return valid;
}

