#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <iostream>
#include "Board.h"

using std::string;

// forward declaration for pointer
class Board; 

/**
 * @brief Base class for all chess pieces.
 */
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
        /**
         * @brief Initialize a "dead" piece, i.e. a empty space at the board.
         */
        Piece();

        /**
         * @brief A generic "piece" that has a color and is alive. Not to be
         * used in a standard game of chess.
         *
         * @param color Piece side color (white == 1, black == 0)
         * @param _gameBoard Board piece resides on.
         */
        Piece(const bool& color, Board* _gameBoard);

        /**
         * @brief Default destructor. No memory to deallocate here.
         */
        virtual ~Piece() = default;

        /**
         * @brief Query piece side/colour. 
         *
         * @return True if white, false if black.
         */
        [[nodiscard]] bool isWhite() const {return white;}

        /**
         * @brief Query if piece is alive. Real piece on the board is alive,
         * dead are empty spaces.
         *
         * @return true if alive
         */
        [[nodiscard]] bool isAlive() const {return alive;}

        /**
         * @brief Query piece type
         *
         * @return 'q', 'k', 'p', 'r', 'n' or 'b'. Ordinary piece (this) is 'u'.
         */
        [[nodiscard]] char getType() const {return type;}

        /**
         * @brief Get image associated to piece. 
         *
         * @return image of piece, xpm formatted image in 2d array.
         */
        [[nodiscard]] const char** getImage() const {return img;}

        /**
         * @brief Query if a piece can move to a postion
         *
         * @param oldX Piece current column position
         * @param oldY Piece current row position 
         * @param newX Piece "move to" position (column)
         * @param newY Piece "move to" row position.
         * @param b 2d piece array this piece resides on
         * @param testCheck Want to test for check on moving?
         *
         * @return Base class always return true (cheating piece).
         */
        virtual bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) { std::cout << "## Piece validMove() - always true ##\n"; return true; }

        /**
         * @brief Query if a piece controls a postion
         *
         * @param oldX Piece current column position
         * @param oldY Piece current row position 
         * @param newX Piece test position (column)
         * @param newY Piece test row position.
         * @param b 2d piece array this piece resides on
         * @param testCheck Want to test for check on moving?
         *
         * @return Base class always return true (cheating piece).
         */
        virtual bool controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) { std::cout << "## Piece controlsSquare() - always true ##\n"; return true; }

        /**
         * @brief Test if a position contains a check on "this" side
         *
         * @param b A "board" of chess pieces, 2d pointer Piece array
         *
         * @return true if checked
         */
        bool isChecked(Piece*** b) const;

        /**
         * @brief Test if a future position would make a check. Makes a copy
         * of the board, transfers the move and calls isChecked(Piece***).
         *
         * @param oldX Old column position
         * @param oldY Old row postion
         * @param newX New column position
         * @param newY New row position
         *
         * @return true if future position is check
         */
        bool isChecked(const int& oldX, const int& oldY, const int& newX, const int& newY);


        /**
         * @brief Get value of piece
         *
         * @return Value of piece
         */
        virtual double getValue() {return value;}

        /**
         * @brief Test if piece has moved
         *
         * @return True if piece have never moved in game. Useful
         * for testing castling
         */
        [[nodiscard]] bool hasNotMoved() const {return notMoved;}

        /**
         * @brief Upon a pice moving, this should be called to set
         * notMoved flag to false.
         */
        void hasMoved() {notMoved = false;}
};

#endif
