#ifndef BOARD_H
#define BOARD_H

class Piece; // Forward declatation for pointers

class Board{
    private:
        Piece*** board;
        int moveCount;
        void setStandardBoard();

    public:
        Board();
        ~Board();
        Piece*** getBoard() {return board;}
        Piece* getPieceAt(int arrX, int arrY);
        bool movePiece(int oldX, int oldY, int newX, int newY);
        bool atMove() const { return moveCount % 2;}
        bool testCheck();
        bool testMate();
        

};

#endif
