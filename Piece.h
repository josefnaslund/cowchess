#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <iostream>
#include "Piece.h"

using std::string;

class Piece {
    protected:
        bool alive;
        bool white;
        const char** img;

    public:
        Piece();
        Piece(const bool& color);
        virtual ~Piece() {};

        bool isWhite() const {return white;}
        bool isAlive() const {return alive;}
        const char** getImage() const {return img;}
        void killPiece(){alive = false;}

        virtual bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b) { std::cout << "## Piece validMove() - always true ##\n"; return true; }
};

#endif
