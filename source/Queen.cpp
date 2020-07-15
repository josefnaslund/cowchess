#include <cmath>
#include "Queen.h"
#include "queen_w.xpm"
#include "queen_b.xpm"


using std::cout;
using std::endl;

Queen::Queen(bool color, Board* _gameBoard) 
    : 
        Piece(color, _gameBoard),
        Rook(color, _gameBoard),
        Bishop(color, _gameBoard){ 


            alive = true;
            white = color;
            type = 'q';
            value = 9.0;


            if (color){
                img = queen_w_xpm;
            }

            else {
                img = queen_b_xpm;
            }

            gameBoard = _gameBoard;

            notMoved = true;

        }

bool Queen::validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){

    return (rookValidMove(oldX, oldY, newX, newY, b, testCheck) || bishopValidMove(oldX, oldY, newX, newY, b, testCheck));
}


bool Queen::controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){
    return (rookControlsSquare(oldX, oldY, newX, newY, b, testCheck) || bishopControlsSquare(oldX, oldY, newX, newY, b, testCheck));
}
