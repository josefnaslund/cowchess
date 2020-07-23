#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "LastMove.h"
#include "Player.h"

class Piece; // Forward declatation for pointers

using std::vector;

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
        Board();
        Board(const Board& _gameBoard);
        ~Board();
        Piece*** getBoard() {return board;}
        Piece* getPieceAt(int arrX, int arrY);
        bool movePiece(int oldX, int oldY, int newX, int newY);
        bool atMove() const { return moveCount % 2;}
        bool testCheck();
        bool testMate();
        bool playerCanMove();
        const LastMove& getLastMove() const {return lastMove;}
        bool getPlayerAI(bool player) const;
        Player* getPlayers() {return players;}
        const bool isPromotion() const {return promotion;}
        void setPromotion(bool prom) {promotion = prom;}
        void setPromotionChar(char p) {promotionChar = p;}
        const int& getPromotionOldX() const {return promotionOldX;}
        const int& getPromotionOldY() const {return promotionOldY;}
        const int& getPromotionNewX() const {return promotionNewX;}
        const int& getPromotionNewY() const {return promotionNewY;}
        const char& getPromotionChar() const {return promotionChar;}
        const vector<Piece*>& getCapturedPieces() const {return capturedPieces;}
        void setSilent() {silent = true;}

};

#endif
