#ifndef LASTMOVE_H
#define LASTMOVE_H

#include <iostream>

/**
 * @brief Two purposes of this class:
 *  1) store info about last move in Board object, so it can determine if
 *  'en passant' move is possible.
 *
 *  2) Print made moves to standard output.
 *
 */
class LastMove {
    private:
        int oldX;
        int oldY;
        int newX;
        int newY;
        char type; // type of piece
        bool capture;
        char promotion;
        bool check;
        bool noMovesPossible;
        bool shortCastling;
        bool longCastling;
        bool moveColor;

    public:
        LastMove();
        LastMove(int _oldX, int _oldY, int _newX, int _newY, 
                char _type, bool _capt, char _prom, bool _check, bool _noMoves,
                bool shortCastling, bool longCastling, bool _moveColor);

        [[nodiscard]] const int& getOldX() const { return oldX; }
        [[nodiscard]] const int& getOldY() const { return oldY; }
        [[nodiscard]] const int& getNewX() const { return newX; }
        [[nodiscard]] const int& getNewY() const { return newY; }
        [[nodiscard]] const char& getType() const { return type; }
        [[nodiscard]] const bool& getCapture() const { return capture; }
        [[nodiscard]] const char& getPromotion() const { return promotion; }
        [[nodiscard]] const bool& isCheck() const {return check;}
        [[nodiscard]] const bool& noMoves() const {return noMovesPossible;}
        [[nodiscard]] const bool& getShortCastling() const {return shortCastling;}
        [[nodiscard]] const bool& getLongCastling() const {return longCastling;}
        [[nodiscard]] const bool& getMoveColor() const { return moveColor;}



};

std::ostream& operator<<(std::ostream& os, const LastMove& lm);



#endif
