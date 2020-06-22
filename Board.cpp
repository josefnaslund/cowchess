#include <iostream>
#include "Board.h"
#include "Piece.h"
#include "constants.h"

using std::cout, std::endl;

Board::Board(){
    // white begins
    moveCount = 1;

    // Allocate memory for multi dimensional array
    board = new Piece*[8];
    for (int i = 0; i != 8; ++i){
        board[i] = new Piece[8];
    }


    // assign empty/dead pieces to all slots
    for (int i = 0; i != 8; ++i){
        for (int j = 0; j != 8; ++j){
            board[i][j] = Piece();
        }
    }

    // Some real pieces
    board[0][4] = Piece(1);
    board[7][4] = Piece(0);
}


Piece* Board::getPieceAt(int arrX, int arrY){
    cout << "Board.getPieaceAt(" << arrX << ", " << arrY << ")\n";
    cout << "is alive: " << board[arrY][arrX].isAlive() << endl;


    return &board[arrY][arrX];
}


bool Board::movePiece(int oldX, int oldY, int newX, int newY){
        if (board[oldX][oldY].validMove(oldX, oldY, newX, newY)){
            cout << "*It's a valid move\n";
            // replace new square with old piece
                board[newY][newX] = board[oldY][oldX];

                
                // Debug - query piece
                cout << "*Piece at [" << oldX << "][" << oldY <<"] is: " <<
                    board[oldX][oldY].isAlive() << endl;

                // kill old piece
                board[oldY][oldX].killPiece();


        }
}
