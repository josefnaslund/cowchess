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


};

#endif
