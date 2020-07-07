#include <cmath>
#include "Move.h"

Move::Move(){
        invalid = true;
}

Move::Move(int& _oldX, int& _oldY, int& _newX, int& _newY, Board* _gameBoard){
    invalid = false;
    gameBoard = _gameBoard;
    board = gameBoard->getBoard();
    oldX = _oldX;
    oldY = _oldY;
    newX = _newX;
    newY = _newY;
    piece = board[oldY][oldX];

    if (board[newY][newX]->isAlive() && 
            (piece->isWhite() != board[newY][newX]->isWhite())
       )
    {
        captureValue = board[newY][newX]->getValue();
    }

    // Catch 'en passant' by pawn
    else if ( piece->getType() == 'p' && (oldX != newX) && !(board[newY][newX]->isAlive()) ){
        captureValue = 0;

        // test 'en passant'
        const LastMove& lm = gameBoard->getLastMove();
        // last piece is pawn...
        if (lm.getType() == 'p'){

            if ( // ...that pawn moved 2 squares forward...
                    abs(lm.getOldY() - lm.getNewY()) == 2 &&

                    // ...and it is on same row as this one...
                    (oldY == lm.getNewY()) &&

                    // ... they are next to each other (columns)
                    (abs(lm.getNewX() - oldX) == 1) &&

                    // ... and they would have been on same cols
                    newX == lm.getNewX()
               )
            {
                captureValue = 1;
            }

        }
    }


    else {
        captureValue = 0;
    }

    check = captureValue && (board[newY][newX]->getType() == 'k');

}
