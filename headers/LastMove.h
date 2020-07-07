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

    public:
        LastMove();
        LastMove(int _oldX, int _oldY, int _newX, int _newY, 
                char _type, bool _capt, char _prom, bool _check);

        const int& getOldX() const { return oldX; } 
        const int& getOldY() const { return oldY; } 
        const int& getNewX() const { return newX; } 
        const int& getNewY() const { return newY; } 
        const char& getType() const { return type; }
        const bool& getCapture() const { return capture; }
        const char& getPromotion() const { return promotion; }
        const bool& isCheck() const {return check;}


};

std::ostream& operator<<(std::ostream& os, const LastMove& lm);



#endif
