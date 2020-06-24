#ifndef PIECE_H
#define PIECE_H

#include <string>

using std::string;

class Piece {
    protected:
        bool alive;
        bool white;
        string img;

    public:
        Piece();
        Piece(bool color);

        bool isWhite() const {return white;}
        bool isAlive() const {return alive;}
        string getImage() const {return img;}
        void killPiece(){alive = false;}

        bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY) { return true; }
};

#endif
