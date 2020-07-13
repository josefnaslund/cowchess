#ifndef MOUSE_H
#define MOUSE_H

#include <SDL2/SDL.h>
#include "Board.h"

class Mouse {
    private:
        int posX;
        int posY;
        bool locked;
        Board* gameBoard;

    public:
        Mouse(Board* _gameBoard);
        int getPosX() const {return posX;}
        int getPosY() const {return posY;}
        void setPosX(int _x);
        void setPosY(int _y);

        bool isLocked() const {return locked;}
        void setLocked(bool _l) {locked = _l;}

        bool getIndexPos(const int& guiX, const int& guiY, int& arrX, int& arrY);
        bool mouseEvents(SDL_Event& e, Board& board);

};



#endif
