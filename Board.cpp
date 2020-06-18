#include "Board.h"
#include "Piece.h"

Board::Board(){

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
