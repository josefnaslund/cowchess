#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"

class Piece; // forward

class Move {
    private:
        int oldX;
        int oldY;
        int newX;
        int newY;
        Piece* piece;
        Piece*** board;
        bool check;
        int captureValue;

    public:
        Move(int& _oldX, int& oldY, int& _newX, int& _newY, Piece*** board);

        // void setOldX(const int& _x) {oldX = _x;}
        // void setOldY(const int& _y) {oldY = _y;}
        // void setNewX(const int& _x) {newX = _x;}
        // void setNewY(const int& _y) {newY = _y;}
        // void setPiece(Piece* _piece) {piece = _piece;}

        const int& getOldX() const { return oldX;}
        const int& getOldY() const { return oldY;}
        const int& getNewX() const { return newX;}
        const int& getNewY() const { return newY;}
        const int& getCaptureValue() const {return captureValue;}
        const bool& isCheck() const {return check;}

        Piece* getPiece() const {return piece;}



};


#endif
