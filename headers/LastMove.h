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
        /**
         * @brief Default constructor initializes a non-move, for use at
         * beginning of game when no moves have been made. Position is then
         * negative.
         */
        LastMove();

        /**
         * @brief Initialization constructor gives needed info about a move
         * made.
         *
         * @param _oldX Old column position
         * @param _oldY Old row position
         * @param _newX New column position
         * @param _newY New row position
         * @param _type Char of moved piece type, e.g. 'p', 'q', 'k' etc.
         * @param _capt Is it a capture?
         * @param _prom Is it a promotion? No promotion is 'u'.
         * @param _check Is it a check?
         * @param _noMoves Is there no moves possible?
         * @param shortCastling Is it a short castling?
         * @param longCastling Is it a long castling?
         * @param _moveColor Who made the move, black or white?
         */
        LastMove(int _oldX, int _oldY, int _newX, int _newY, 
                char _type, bool _capt, char _prom, bool _check, bool _noMoves,
                bool shortCastling, bool longCastling, bool _moveColor);

        /**
         * @brief Get old position column
         *
         * @return Index of old column
         */
        [[nodiscard]] const int& getOldX() const { return oldX; }

        /**
         * @brief Get old position row
         *
         * @return  Index of old column
         */
        [[nodiscard]] const int& getOldY() const { return oldY; }

        /**
         * @brief Get new position column
         *
         * @return  Index of column piece moved to
         */
        [[nodiscard]] const int& getNewX() const { return newX; }

        /**
         * @brief Get new position row
         *
         * @return Index of row piece have moved to
         */
        [[nodiscard]] const int& getNewY() const { return newY; }

        /**
         * @brief What char letter does last piece move have?
         *
         * @return 'p', 'k', 'q', 'r', 'n' or 'b'
         */
        [[nodiscard]] const char& getType() const { return type; }

        /**
         * @brief Is it a capture?
         *
         * @return true if capture
         */
        [[nodiscard]] const bool& getCapture() const { return capture; }

        /**
         * @brief Is it promotion?
         *
         * @return  true is a pawn has promoted
         */
        [[nodiscard]] const char& getPromotion() const { return promotion; }

        /**
         * @brief Is it check?
         *
         * @return  True if last move was a check on opponent.
         */
        [[nodiscard]] const bool& isCheck() const {return check;}

        /**
         * @brief Did the last move leave no room for player to move?
         * noMoves() with isCheck() is mate. Only noMoves() is stale mate.
         *
         * @return True if opponent has no moves after this move
         */
        [[nodiscard]] const bool& noMoves() const {return noMovesPossible;}

        /**
         * @brief Is the move a short (kingside) castling?
         *
         * @return true if kingside castling
         */
        [[nodiscard]] const bool& getShortCastling() const {return shortCastling;}

        /**
         * @brief Is the move a long castling (queenside)?
         *
         * @return true if queenside castling
         */
        [[nodiscard]] const bool& getLongCastling() const {return longCastling;}

        /**
         * @brief Who made the move - black or white? 
         *
         * @return True if white player made the move.
         */
        [[nodiscard]] const bool& getMoveColor() const { return moveColor;}



};

/**
 * @brief Overloading operator for printing chess notation for each move made,
 * directly after it is made, to send to standard output.
 *
 * @param os Output stream, that is std::cout (standard output).
 * @param lm The last move made.
 *
 * @return output stream with move info, e.g. "1. e2-e4"
 */
std::ostream& operator<<(std::ostream& os, const LastMove& lm);



#endif
