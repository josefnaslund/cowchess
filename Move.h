#ifndef MOVE_H
#define MOVE_H

class Move {
    private:
        int oldX;
        int oldY;
        int newX;
        int newY;
        Piece*** board
        Piece* piece;
        bool isCapture;
        bool isCheck;

    public:
        Move(int& _oldX, int& oldY, int& _newX, int& _newY, Piece*** _board);

        // void setOldX(const int& _x) {oldX = _x;}
        // void setOldY(const int& _y) {oldY = _y;}
        // void setNewX(const int& _x) {newX = _x;}
        // void setNewY(const int& _y) {newY = _y;}
        // void setPiece(Piece* _piece) {piece = _piece;}

        int& getOldX() const { return oldX;}
        int& getOldY() const { return oldY;}
        int& getNewX() const { return newX;}
        int& getNewY() const { return newY;}
        bool& isCapture() const {return isCapture;}
        bool& isCheck() const {return isCheck;}

        Piece* getPiece() const {return piece;}



};


#endif
