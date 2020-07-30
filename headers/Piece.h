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
        double value;
        bool notMoved;

    public:
        Piece();
        Piece(const bool& color, Board* _gameBoard);
        virtual ~Piece() = default;

        [[nodiscard]] bool isWhite() const {return white;}
        [[nodiscard]] bool isAlive() const {return alive;}
        [[nodiscard]] char getType() const {return type;}
        [[nodiscard]] const char** getImage() const {return img;}
        virtual bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) { std::cout << "## Piece validMove() - always true ##\n"; return true; }
        virtual bool controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) { std::cout << "## Piece controlsSquare() - always true ##\n"; return true; }
        bool isChecked(Piece*** b) const;
        bool isChecked(const int& oldX, const int& oldY, const int& newX, const int& newY);

        virtual double getValue() {return value;}

        [[nodiscard]] bool hasNotMoved() const {return notMoved;}
        void hasMoved() {notMoved = false;}
};

#endif
