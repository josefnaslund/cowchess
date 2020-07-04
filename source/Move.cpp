#include "Move.h"

Move::Move(int& _oldX, int& _oldY, int& _newX, int& _newY, Piece*** _board){
    oldX = _oldX;
    oldY = _oldY;
    newX = _newX;
    newY = _newY;
    board = _board;
    piece = board[oldY][oldX];

    if (board[newY][newX]->isAlive() && 
        (piece->isWhite() != board[newY][newX]->isWhite())
        )
    {
            captureValue = board[newY][newX]->getValue();
    }

    else {
            captureValue = 0;
    }

    check = captureValue && (board[newY][newX]->getType() == 'k');

}
