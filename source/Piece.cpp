#include <iostream>
#include "Piece.h"
#include "piece.xpm"
#include "piece_w.xpm"
#include "piece_b.xpm"

using std::cout; 
using std::endl; 
using std::cerr;

Piece::Piece(){
    white = true;
    alive = false;
    img = piece_xpm;
    type = 'u';
    value = 0.0;
    notMoved = true;
}

Piece::Piece(const bool& color, Board* _gameBoard){

    alive = true;
    white = color;
    type = 'u';
    value = 0.0;

    if (color){
        img = piece_w_xpm ;
    }

    else {
        img = piece_b_xpm;
    }

    gameBoard = _gameBoard;
    notMoved = true;
} 


bool Piece::isChecked(Piece*** testBoard){
    bool checked = false;

    // find king of this color
    int kingX = -1;
    int kingY = -1;
    for (int i = 0; i != 8; ++i){
        for (int j = 0; j != 8; ++j){
            if (testBoard[i][j]->isAlive() && (testBoard[i][j]->isWhite() == isWhite()) && testBoard[i][j]->getType() == 'k'){
                kingX = j; kingY = i;
            }
        }
    }

    if (kingX == -1 || kingY == -1){
        std::cerr << "Error - No king?!?!\n";
    }


    // see if other players pieces can take king
    for (int x = 0; x != 8; ++x){
        for (int y = 0; y != 8; ++y){
            if (testBoard[y][x]->isAlive() && (testBoard[y][x]->isWhite() != testBoard[kingY][kingX]->isWhite()) &&
                testBoard[y][x]->validMove(x, y, kingX, kingY, testBoard, false)){
                checked = true;
                break;
            }
        }
    }


    return checked;

}

bool Piece::isChecked(const int& oldX, const int& oldY, const int& newX, const int& newY){
    Piece*** newBoard;
    Piece*** oldBoard = gameBoard->getBoard();

    // allocate memory
    newBoard = new Piece**[8];
    for (int i = 0; i != 8; ++i){
        newBoard[i] = new Piece*[8];

    }

    // copy old to new
    for (int i = 0; i != 8; ++i){
        for (int j = 0; j != 8; ++j){
            newBoard[i][j] = oldBoard[i][j];
        }
    }

    // make the move on new board
    newBoard[newY][newX] = oldBoard[oldY][oldX];
    newBoard[oldY][oldX] = new Piece();

    // std::cout << "\t***(" << newY << "," << newX << ") is alive(" << 
    //     newBoard[newY][newX]->isAlive() << ") color(" << 
    //     newBoard[newY][newX]->isWhite() << ") type(" << 
    //     newBoard[newY][newX]->getType() << ")" << endl;



    // cout << "***TEMP BOARD***\n";
    // cout << "args: " << oldX << "," << oldY << "," << newX << "," << newY << endl;
    // for (int i = 0; i != 8; ++i){
    //         for (int j = 0; j != 8; ++j){
    //             Piece* p = newBoard[7-i][j];
    //             if (p->isAlive() && p->isWhite()){
    //                     cout << "I";
    //             }

    //             else if (p->isAlive()){
    //                     cout << "i";
    //             }
    //             else {
    //                     cout << "0";
    //             }
    //                 
    //         }
    //         cout << endl;
    // }
    // cout << "****************\n";



    // make the test
    bool checked = isChecked(newBoard);

    // deallocate memory
    // note: don't delete all objects, since they still are in other array.

    delete newBoard[oldY][oldX]; // delete new dead piece from temp board

    for (int i = 0; i != 8; ++i){

        delete[] newBoard[i];
    }
    delete[] newBoard;

    return checked;
}
