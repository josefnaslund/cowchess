#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <iostream>
#include "Board.h"

using std::string;

class Board; // forward declaration for pointer

class Piece {
    protected:
        bool alive;
        bool white;
        const char** img;
        Board* gameBoard;
        char type;

    public:
        Piece();
        Piece(const bool& color, Board* _gameBoard);
        virtual ~Piece() {};

        bool isWhite() const {return white;}
        bool isAlive() const {return alive;}
        char getType() const {return type;}
        const char** getImage() const {return img;}
        void killPiece(){alive = false;}
        virtual bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) { std::cout << "## Piece validMove() - always true ##\n"; return true; }
        bool isChecked(Piece*** b);
        bool isChecked(const int& oldX, const int& oldY, const int& newX, const int& newY);
};

#endif
