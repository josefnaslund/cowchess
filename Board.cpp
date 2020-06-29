#include <iostream>
#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include "King.h"
#include "constants.h"

using std::cout, std::endl;

Board::Board(){
    board = new Piece**[8];
    for (int i = 0; i != 8; ++i){
            board[i] = new Piece*[8];
    }
    
    // white begins
    moveCount = 1;

    // assign empty/dead pieces to all slots
    for (int i = 0; i != 8; ++i){
        for (int j = 0; j != 8; ++j){
            board[i][j] = new Piece();
        }
    }

    setStandardBoard();
}


void Board::setStandardBoard(){
    // Some fictive pieces
    // delete board[1][0];
    // board[1][0] = new Piece(1);

    // delete board[6][0];
    // board[6][0] = new Piece(0);

    // Some real pieces
    delete board[0][0];
    board[0][0] = new Rook(1);

    delete board[7][7];
    board[7][7] = new Rook(0);

    delete board[0][7];
    board[0][7] = new Rook(1);

    delete board[7][0];
    board[7][0] = new Rook(0);


    delete board[0][4];
    board[0][4] = new King(1);
    
    delete board[7][4];
    board[7][4] = new King(0);
}

Board::~Board(){
        // delete pieces
        for (int i = 0; i != 8; ++i){
                for (int j = 0; j != 8; ++j){
                        delete board[i][j];
                }
        }

        // delete arrays
        for (int i = 0; i != 8; ++i){
                delete board[i];
        }


        // final array delete
        delete board;

}


Piece* Board::getPieceAt(int arrX, int arrY){
    return board[arrY][arrX];
}


bool Board::movePiece(int oldX, int oldY, int newX, int newY){
    if (
            (board[oldY][oldX]->isWhite() == (bool)(moveCount % 2)) &&
            (board[oldY][oldX]->validMove(oldX, oldY, newX, newY, board) )
       ){
        cout << "*It's a valid move\n";
        
        // delete old piece
        delete board[newY][newX];


        // replace new square with old piece
        board[newY][newX] = board[oldY][oldX];


        // kill old piece
        //board[oldY][oldX]->killPiece();
        board[oldY][oldX] = new Piece();


        // increment moves/turn
        ++moveCount;


        return true;
    }

    return false;
}
