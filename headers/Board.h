#ifndef BOARD_H
#define BOARD_H

#include "LastMove.h"
#include "Player.h"

class Piece; // Forward declatation for pointers

class Board{
    private:
        Player* players;
        Piece*** board;
        int moveCount;
        void setStandardBoard();
        LastMove lastMove;
        bool promotion;
        char promotionChar;
        int promotionOldX;
        int promotionOldY;
        int promotionNewX;
        int promotionNewY;


    public:
        Board();
        ~Board();
        Piece*** getBoard() {return board;}
        Piece* getPieceAt(int arrX, int arrY);
        bool movePiece(int oldX, int oldY, int newX, int newY);
        bool atMove() const { return moveCount % 2;}
        bool testCheck();
        bool testMate();
        bool playerCanMove();
        const LastMove& getLastMove() {return lastMove;}
        bool getPlayerAI(bool player);
        Player* getPlayers() {return players;}
        bool isPromotion() {return promotion;}
        void setPromotion(bool prom) {promotion = prom;}
        void setPromotionChar(char p) {promotionChar = p;}
        const int& getPromotionOldX() const {return promotionOldX;}
        const int& getPromotionOldY() const {return promotionOldY;}
        const int& getPromotionNewX() const {return promotionNewX;}
        const int& getPromotionNewY() const {return promotionNewY;}

};

#endif
