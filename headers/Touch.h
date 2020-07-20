#ifndef TOUCH_H
#define TOUCH_H

#include <SDL2/SDL.h>
#include <utility>
#include "Board.h"

class Touch {
    private:
        int posX;
        int posY;
        bool locked;
        std::pair<int, int> absoluteLockedPosition;
        std::pair<int, int> absoluteCurrentPosition;
        Board* gameBoard;

    public:
        Touch(Board* _gameBoard);
        int getPosX() const {return posX;}
        int getPosY() const {return posY;}
        void setPosX(int _x);
        void setPosY(int _y);

        bool isLocked() const {return locked;}
        void setLocked(bool _l) {locked = _l;}

        std::pair<int, int> getAbsoluteLockedPosition() { return absoluteLockedPosition;}
        std::pair<int, int> getAbsoluteCurrentPosition() { return absoluteCurrentPosition;}

        bool getIndexPos(const int& guiX, const int& guiY, int& arrX, int& arrY);
        bool touchEvents(SDL_Event& fe, Board& board);

};



#endif
