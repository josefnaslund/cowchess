#include <locale> // toupper
#include "LastMove.h"

LastMove::LastMove(){
    oldX = -1;
    oldY = -1;
    newX = -1;
    newY = -1;
    type = 'u';
    capture = false;
    promotion = 'u';
    check = false;
    noMovesPossible = false;
    shortCastling = false;
    longCastling = false;
    moveColor = 0;
}

LastMove::LastMove(int _oldX, int _oldY, int _newX, int _newY, 
        char _type, bool _capt, char _prom, bool _check, bool _noMoves, 
        bool _shortCastling, bool _longCastling, bool _moveColor){
    oldX = _oldX; 
    oldY = _oldY; 
    newX = _newX; 
    newY = _newY; 
    type = _type;
    capture = _capt;
    promotion = _prom;
    check = _check;
    noMovesPossible = _noMoves;
    shortCastling = _shortCastling;
    longCastling = _longCastling;
    moveColor = _moveColor;
}

std::ostream& operator<<(std::ostream& os, const LastMove& lm){

    if (lm.getShortCastling()){
        os << "O-O";
    }

    else if (lm.getLongCastling()){
            os << "O-O-O";
    }

    else {


        if (lm.getType() != 'p'){
            os << static_cast<char>(std::toupper(lm.getType()));
        }

        os << char('a' + lm.getOldX()) << (lm.getOldY() + 1); 

        if (lm.getCapture()){
            os << 'x';
        }

        else {
            os << '-';
        }

        // row
        os << char('a' + lm.getNewX()) << (lm.getNewY() + 1);

        if (lm.getPromotion() != 'u'){
            os << '=' << static_cast<char>(std::toupper(lm.getPromotion()));
        }
    }

    if (lm.isCheck() && lm.noMoves()){
        os << "#\n";
        // White wins
        if (lm.getMoveColor() % 2){
                os << "\t1 - 0\n";
        }
        // black wins
        else {
                os << "\t0 - 1\n";
        }
    }

    else if (lm.isCheck()){
        os << '+';
    }

    // draw
    else if (lm.noMoves()){
        os << "\n½ - ½\n";
    }
    

    return os;

}
