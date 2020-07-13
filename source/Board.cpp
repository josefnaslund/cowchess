#include <iostream>
#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include "King.h"
#include "Pawn.h"
#include "constants.h"


using std::cout; 
using std::endl;

Board::Board(){
    players = new Player[2];
    players[0] = Player(0);
    players[1] = Player(0);


    lastMove = LastMove();

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
    // Rooks
    delete board[0][0];
    board[0][0] = new Rook(1, this);

    delete board[7][7];
    board[7][7] = new Rook(0, this);

    delete board[0][7];
    board[0][7] = new Rook(1, this);

    delete board[7][0];
    board[7][0] = new Rook(0, this);


    // Kings
    delete board[0][4];
    board[0][4] = new King(1, this);

    delete board[7][4];
    board[7][4] = new King(0, this);

    // Pawns
    for (int i = 0; i != 8; ++i){
        delete board[1][i];
        board[1][i] = new Pawn(1, this);

        delete board[6][i];
        board[6][i] = new Pawn(0, this);
    }


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
        delete[] board[i];
    }


    // final array delete
    delete[] board;


    // delete player array
    delete[] players;

}


Piece* Board::getPieceAt(int arrX, int arrY){
    return board[arrY][arrX];
}


bool Board::movePiece(int oldX, int oldY, int newX, int newY){
    if (
            (board[oldY][oldX]->isWhite() == (bool)(moveCount % 2)) &&
            (board[oldY][oldX]->validMove(oldX, oldY, newX, newY, board, true) )
       ){

        // store for LastMove object
        char lmType = board[oldY][oldX]->getType();
        bool lmCapt = board[newY][newX]->isAlive();
        char lmProm = 'u';


        // detect passant
        if (lmType == 'p' && (!lmCapt) && (oldX != newX)){
            lmCapt = true;
            delete board[lastMove.getNewY()][lastMove.getNewX()];
            board[lastMove.getNewY()][lastMove.getOldX()] = new Piece();
        }


        // delete old piece
        delete board[newY][newX];


        // replace new square with old piece
        board[newY][newX] = board[oldY][oldX];


        // kill old piece
        board[oldY][oldX] = new Piece();


        // increment moves/turn
        ++moveCount;

        // temp. promovation
        if ( 
                (board[newY][newX]->getType() == 'p') &&
                (newY == 0 || newY == 7)
           ) 
        {


            bool col = board[newY][newX]->isWhite();
            delete board[newY][newX];
            board[newY][newX] = new Rook(col, this);

            // store for LastMove object
            lmProm = board[newY][newX]->getType();

        }

        bool lmCheck = testCheck();
        bool lmNoMoves = !playerCanMove();

        lastMove = LastMove(oldX, oldY, newX, newY, lmType, lmCapt, lmProm,
                lmCheck, lmNoMoves);


        // print move list

        if (!atMove())
            cout << moveCount / 2 + moveCount % 2 << ". ";
        cout << lastMove << std::flush;
        if (atMove())
            cout << endl;
        else
            cout << " ";




        return true;
    }

    return false;
}

bool Board::testCheck(){
    // cout << "\t--* Testing check for player " << atMove() << endl;
    Piece* p;

    for (int i = 0; i != 8; ++i){
        for (int j = 0; j != 8; ++j){
            p = board[i][j];

            // to only test each side once, test on king
            if (
                    p->getType() == 'k' && ( p->isWhite() == atMove() ) && 
                    p->isChecked(board)
               )
            {
                return true;
            }
        }
    }

    return false;
}

bool Board::testMate(){
    Piece* p;

    // find checked players pieces, test if any move can uncheck
    if (testCheck()){
        for (int i = 0; i != 8; ++i){
            for (int j = 0; j != 8; ++j){
                p = board[j][i];
                if (p->isAlive() && (p->isWhite() == atMove())){
                    // test valid moves for piece
                    for (int ii = 0; ii != 8; ++ii){
                        for (int jj = 0; jj != 8; ++jj){
                            if (p->validMove(i, j, ii, jj, board, 1)){
                                // cout << 
                                //     "\t--* A valid move is found: move piece at (" << 
                                //     j << "," << i << ") to (" << jj << "," << 
                                //     ii << ").\n";
                                return false; // return 1
                            }
                            else {
                                // cout << "\t--* Can't move (" << j << "," << 
                                //     i << ") ti (" << jj << "," << ii << 
                                //     ").\n";
                            }
                        }

                    }
                }
            }
        }
        return true;
    }
    return false;
}



bool Board::playerCanMove(){
    Piece* p;

    // find current players moveability for each piece
    for (int i = 0; i != 8; ++i){
        for (int j = 0; j != 8; ++j){
            p = board[j][i];
            if (p->isAlive() && (p->isWhite() == atMove())){
                // test valid moves for piece
                for (int ii = 0; ii != 8; ++ii){
                    for (int jj = 0; jj != 8; ++jj){
                        if (p->validMove(i, j, ii, jj, board, 1)){
                            return true; // first return
                        }
                        else {
                            // cout << "\t--* Can't move (" << j << "," << 
                            //     i << ") ti (" << jj << "," << ii << 
                            //     ").\n";
                        }
                    }

                }
            }
        }
    }
    return false;       
}

bool Board::getPlayerAI(bool player){
    return players[player].isAI();
}
