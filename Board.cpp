#include <iostream>
#include "Board.h"
#include "Piece.h"
#include "constants.h"

using std::cout, std::endl;

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

Piece* Board::getPieceAt(int x, int y){
    if (x < LEFT_MARGIN || x > LEFT_MARGIN + 8 * SQUARE_SIZE || 
            y < TOP_MARGIN || y > TOP_MARGIN + 8 * SQUARE_SIZE){
        cout << "Outside of square: " << x << "," << y << "\n";
        cout << "Returning null\n";
        return NULL;
    }

    cout << "Board - Piece at pos: " << x << "," << y << " : ";


    // chess position x
    cout << (char)(65 + (x - LEFT_MARGIN) / 50);

    // chess position y
    cout << (7 - (y - TOP_MARGIN) / 50) + 1<< endl;

    cout << "Board - Returning piece at board[" << 
        7 - (y - TOP_MARGIN) / 50 << "][" <<
        (x - LEFT_MARGIN) / 50 << "]\n";

    return &board[7 - (y - TOP_MARGIN) / 50][(x - LEFT_MARGIN) / 50];




}
