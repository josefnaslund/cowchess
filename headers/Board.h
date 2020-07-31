#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "LastMove.h"
#include "Player.h"

class Piece; // Forward declatation for pointers

using std::vector;

/**
 * @brief Contains info about a bord position, either "as is" in the game
 * or a calculation of possible moves by AI. Keeps track of who is to move,
 * players in the game (human or AI), and importantly the 2d array of Piece*
 * wich make up the game board. Stores captured pieces in vector for display.
 */
class Board{
    protected:
        Piece*** board;

    private:
        Player* players;
        int moveCount;
        void setStandardBoard();
        LastMove lastMove;
        bool promotion;
        char promotionChar;
        int promotionOldX;
        int promotionOldY;
        int promotionNewX;
        int promotionNewY;
        vector<Piece*> capturedPieces;
        bool silent;
        


    public:
        /**
         * @brief Default constructor to initialise a start up game
         */
        Board();

        /**
         * @brief Copy constructor. Used for copying a Board object. Used 
         * by AI to evaluate testing positions
         *
         * @param _gameBoard The board to be copied
         */
        Board(const Board& _gameBoard);

        /**
         * @brief Destructor deallocates dynamic memory, most importantly
         * the allocated 2d array containing allocated pieces.
         */
        ~Board();

        /**
         * @brief Get the actual board (Piece array)
         *
         * @return 2d Piece* array that makes up the position of Board object.
         */
        Piece*** getBoard() {return board;}

        /**
         * @brief Get piece at a specific location. Remember that non-occupied
         * squares have an allocated "dead" piece at it's position in the
         * array.
         *
         * @param arrX Column
         * @param arrY Row
         *
         * @return Pointer to piece at position, either "dead" or "alive"
         */
        Piece* getPieceAt(int arrX, int arrY);

        /**
         * @brief Used for moving pieces. If a valid move is made, a LastMove
         * object is stored with info about the move. This member function
         * neeeds to be called twice when promoting a pawn, first with the pawn
         * move, then with info stored about promotionChar, i.e. piece to
         * promote to.
         *
         * @param oldX "Moving from"-column
         * @param oldY "Moving from"-row
         * @param newX "Moving to"-column
         * @param newY "Moving to"-row
         *
         * @return true if move is made (a valid move)
         */
        bool movePiece(int oldX, int oldY, int newX, int newY);

        /**
         * @brief Get info about who is to play
         *
         * @return White to play == 1, black to play == 0
         */
        [[nodiscard]] bool atMove() const { return moveCount % 2;}

        /**
         * @brief Test if either side is checked
         *
         * @return True if a king is checked
         */
        bool testCheck();

        /**
         * @brief Test if player has moves. To detect mate or stale mate.
         * Only test current player at the move.
         * 
         *
         * @return True if player has possible moves
         */
        bool playerCanMove();


        /**
         * @brief Get info about the last made move. A must have
         * for detecting "en passant" moves, but this is also used for
         * sending the move notation to standard output. That is done
         * with overloading operator<< for class.
         *
         * @return A reference to last move made (positions, piece type, etc.)
         */
        [[nodiscard]] const LastMove& getLastMove() const {return lastMove;}

        /**
         * @brief Query if player is AI.
         *
         * @param player Player 1 (white) or 0 (black).
         *
         * @return True if "player"(1 or 0) is AI.
         */
        [[nodiscard]] bool getPlayerAI(bool player) const;

        /**
         * @brief Get array of players
         *
         * @return Array of players with info about AI.
         */
        Player* getPlayers() {return players;}

        /**
         * @brief Get info if a current or last move is a promotion move.
         *
         * @return True if a pawn has just been moved to last rank.
         */
        [[nodiscard]] bool isPromotion() const {return promotion;}


        /**
         * @brief Set promotion true if a promotion is happening. Called
         * by makeMove(...) to abort finishing the move and query for 
         * promotion piece
         *
         * @param prom Set promotion true or false
         */
        void setPromotion(bool prom) {promotion = prom;}

        /**
         * @brief If a promotion is happening, this function sets the piece
         * to promote to. E.g. 'n' for knight, 'q' for queen, etc.
         *
         * @param prom 'r' for rook, 'n' for knight, 'b' for bishop and
         * 'q' for queen.
         */
        void setPromotionChar(char p) {promotionChar = p;}

        /**
         * @brief Get the promoting pawn old position column
         *
         * @return Column of pawn position before moving to final row
         */
        [[nodiscard]] const int& getPromotionOldX() const {return promotionOldX;}

        /**
         * @brief Get the promoting pawn old position row
         *
         * @return Row of pawn position before moving to final row
         */
        [[nodiscard]] const int& getPromotionOldY() const {return promotionOldY;}

        /**
         * @brief Get the promoting pawn new position column
         *
         * @return Column of promoted piece position after 
         * pawn moving to final row
         */
        [[nodiscard]] const int& getPromotionNewX() const {return promotionNewX;}

        /**
         * @brief Get the promoting pawn new position row
         *
         * @return Row of promoted piece position after 
         * pawn moving to final row
         */
        [[nodiscard]] const int& getPromotionNewY() const {return promotionNewY;}

        /**
         * @brief Character of pawn promotion piece. E.g. 'q' for queen etc.
         *
         * @return 'q', 'n', 'b' or 'r'
         */
        [[nodiscard]] const char& getPromotionChar() const {return promotionChar;}

        /**
         * @brief Get vector of captured pieces from game, so that they can
         * be illustrated on side of board in GUI.
         *
         * @return A reference to vector containing Piece pointers.
         */
        [[nodiscard]] const vector<Piece*>& getCapturedPieces() const {return capturedPieces;}

        /**
         * @brief When AI is testing out moves, it should not print out the
         * moves it tries. So this silece the standard output for moves made.
         */
        void setSilent() {silent = true;}

};

#endif
