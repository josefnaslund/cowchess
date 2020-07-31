#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"

/**
 * @brief AI uses AIMove for making and evaluating moves recusively.
 */
class AIMove {
    private:
        int oldX;
        int oldY;
        int newX;
        int newY;

    public:
        /**
         * @brief Constructor with "moving from" and "moving to" positions.
         *
         * @param _oldX Moving from column.
         * @param oldY Moving from row.
         * @param _newX Moving to column.
         * @param _newY Moving to row.
         */
        AIMove(int _oldX, int oldY, int _newX, int _newY);

        /**
         * @brief Get moving from column value.
         *
         * @return Column value (A==0, B==1, etc).
         */
        [[nodiscard]] const int& getOldX() const { return oldX;}

        /**
         * @brief Get moving from row value.
         *
         * @return Row value (White king row == 0, white pawn row == 1, etc).
         */
        [[nodiscard]] const int& getOldY() const { return oldY;}

        /**
         * @brief Get "moving to" column value.
         *
         * @return Column value (A==0, etc).
         */
        [[nodiscard]] const int& getNewX() const { return newX;}

        /**
         * @brief Get "moving to" row value.
         *
         * @return Row value (White king row == 0, etc.).
         */
        [[nodiscard]] const int& getNewY() const { return newY;}
};

#endif
