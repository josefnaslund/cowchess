#include "Move.h"

Move::Move(int& _oldX, int& oldY, int& _newX, int& _newY, Piece*** _board){
    oldX = _oldX;
    oldY = _oldY;
    newX = _newX;
    newY = _newY;
    board = _board;
    piece = board[oldY][oldX];

    isCapture = board[newY][newX]->isAlive() && 
        (piece->isWhite != board[newY][newX]->isWhite());

    isCheck = isCapture && (board[newY][newX]->getType() == 'k');

}
