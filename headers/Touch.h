#ifndef TOUCH_H
#define TOUCH_H

#include <SDL2/SDL.h>
#include <utility>
#include "Board.h"

/**
 * @brief Handles touch screen input for GUI. Moving pieces, 
 * turn on/off AI, select promotion piece.
 * Similar to Mouse class.
 */
class Touch {
    private:
        int posX;
        int posY;

        // Theese variables are used when touch screen finger have "locked in" 
        // on a piece for moving
        bool locked;
        std::pair<int, int> absoluteLockedPosition;
        std::pair<int, int> absoluteCurrentPosition;
        Board* gameBoard;

    public:
        /**
         * @brief Construct with access to Board object
         *
         * @param _gameBoard Board object to access piece positions
         */
        explicit Touch(Board* _gameBoard);

        /**
         * @brief Get column index (note: index!) position 
         *
         * @return Array index column position of "finger" interaction
         */
        [[nodiscard]] int getPosX() const {return posX;}

        /**
         * @brief Get row index (note: index!) position
         *
         * @return Array index row position of "finger" interaction
         */
        [[nodiscard]] int getPosY() const {return posY;}

        /**
         * @brief Set column index (note: index!) postion
         *
         * @param _x The index of finger interacted position
         */
        void setPosX(int _x);
        
        /**
         * @brief Set row index (note: index!) postion
         *
         * @param _x The row of finger interacted position
         */
        void setPosY(int _y);

        /**
         * @brief Query if the finger is "locked in" on a piece (moving)
         *
         * @return True if a piece is grabbed
         */
        [[nodiscard]] bool isLocked() const {return locked;}

        /**
         * @brief Set locked, if finger is "grabbing" a piece
         *
         * @param _l True if finger is pressed over a piece who is "alive". 
         * Setting to false upon releasing finger.
         */
        void setLocked(bool _l) {locked = _l;}

        /**
         * @brief Get the x-y (column, row) GUI position (not array index) 
         * of touch finger locked position.
         *
         * @return A std::pair of integer with x y coordinates to where it was
         * pressed
         */
        std::pair<int, int> getAbsoluteLockedPosition() { return absoluteLockedPosition;}

        /**
         * @brief Get the x-y (column, row) GUI position (not array index) 
         * of touch finger position.
         *
         * @return A std::pair of integer with x y coordinates
         */
        std::pair<int, int> getAbsoluteCurrentPosition() { return absoluteCurrentPosition;}

        /**
         * @brief Query if a given GUI position is within the boundaries of the
         * 8x8 chess squares.
         *
         * @param guiX GUI column position
         * @param guiY GUI row position
         * @param arrX Array index (column) if queried position is within array
         * @param arrY Arrray index (row) if queried position is within array
         *
         * @return true if position is within chess board on GUI.
         */
        bool getIndexPos(const int& guiX, const int& guiY, int& arrX, int& arrY);

        /**
         * @brief Handles touch events. Functionalityt to move pieces and 
         * touch/click "icons", for
         * AI and pawn promotion
         *
         * @param e SDL_Event
         * @param board Reference to playing Board object.
         *
         * @return true if valid move is made with touch finger.
         */
        bool touchEvents(SDL_Event& fe, Board& board);

};



#endif
