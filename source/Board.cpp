#include <iostream>
#include <iomanip>
#include <string>
#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "constants.h"


using std::cout; 
using std::endl;

Board::Board(){
    // for use by promotion
    promotion = false;
    promotionChar = 'u';
    promotionOldX = -1;
    promotionOldY = -1;
    promotionNewX = -1;
    promotionNewY = -1;

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

    silent = false;
}

// copy constructor used by AI
Board::Board(const Board& _gameBoard){
    this->promotion = _gameBoard.isPromotion();
    this->promotionChar = _gameBoard.getPromotionChar();
    this->promotionOldX = _gameBoard.getPromotionOldX();
    this->promotionOldY = _gameBoard.getPromotionOldY();
    this->promotionNewX = _gameBoard.getPromotionNewX();
    this->promotionNewY = _gameBoard.getPromotionNewY();

    players = new Player[2];
    players[0] = _gameBoard.getPlayerAI(0);
    players[1] = _gameBoard.getPlayerAI(1);

    lastMove = _gameBoard.getLastMove();

    board = new Piece**[8];
    for (int i = 0; i != 8; ++i){
        board[i] = new Piece*[8];
    }

    moveCount = _gameBoard.atMove();

    // copy old board to new
    for (int i = 0; i != 8; ++i){
        for (int j = 0; j != 8; ++j){
            if (_gameBoard.board[i][j]->getType() != 'u'){
                char type = _gameBoard.board[i][j]->getType();
                bool color = _gameBoard.board[i][j]->isWhite();
                if (type == 'k'){
                    board[i][j] = new King(color, this);
                }
                else if (type == 'q'){
                    board[i][j] = new Queen(color, this);
                }
                else if (type == 'b'){
                    board[i][j] = new Bishop(color, this);
                }
                else if (type == 'n'){
                    board[i][j] = new Knight(color, this);
                }
                else if (type == 'r'){
                    board[i][j] = new Rook(color, this);
                }
                else if (type == 'p'){
                    board[i][j] = new Pawn(color, this);
                }
            }

            else {
                board[i][j] = new Piece();
            }
        }
    }

    silent = true;
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

    // knights
    delete board[0][1];
    board[0][1] = new Knight(1, this);

    delete board[7][1];
    board[7][1] = new Knight(0, this);

    delete board[0][6];
    board[0][6] = new Knight(1, this);

    delete board[7][6];
    board[7][6] = new Knight(0, this);

    // bishops
    delete board[0][2];
    board[0][2] = new Bishop(1, this);

    delete board[7][2];
    board[7][2] = new Bishop(0, this);

    delete board[0][5];
    board[0][5] = new Bishop(1, this);

    delete board[7][5];
    board[7][5] = new Bishop(0, this);

    // queens
    delete board[0][3];
    board[0][3] = new Queen(1, this);

    delete board[7][3];
    board[7][3] = new Queen(0, this);

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

    // delete vector captured pieces
    for (auto p : capturedPieces){
        delete p;
    }

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
        bool lmShortCastling = false, lmLongCastling = false;
        bool lmMoveColor = board[oldY][oldX]->isWhite();

        // temp. promotion
        if (promotion && promotionChar != 'u'){
            lmProm = promotionChar;
            bool col = board[oldY][oldX]->isWhite();
            delete board[oldY][oldX];

            if (promotionChar == 'n'){
                board[oldY][oldX] = new Knight(col, this);
            }

            else if (promotionChar == 'r'){
                board[oldY][oldX] = new Rook(col, this);
            }

            else if (promotionChar == 'b'){
                board[oldY][oldX] = new Bishop(col, this);
            }

            else if (promotionChar == 'q'){
                board[oldY][oldX] = new Queen(col, this);
            }



            // store for LastMove object
            lmProm = board[newY][newX]->getType();

            lmProm = promotionChar;
            promotionChar = 'u';
            promotion = false;
        }

        // the promotion move has been made but not choosen
        else if (promotion){
            return false;
        }

        // set 'promotion'
        else if ( 
                (board[oldY][oldX]->getType() == 'p') &&
                (newY == 0 || newY == 7)
                ) 
        {
            promotion = true;
            promotionOldX = oldX;
            promotionOldY = oldY;
            promotionNewX = newX;
            promotionNewY = newY;
            return false;
        }

        else {
        }

        // detect passant
        if (lmType == 'p' && (!lmCapt) && (oldX != newX)){
            lmCapt = true;
            capturedPieces.push_back(board[lastMove.getNewY()][lastMove.getNewX()]);
            board[lastMove.getNewY()][lastMove.getOldX()] = new Piece();
        }

        // detect short castling
        if (board[oldY][oldX]->getType() == 'k' && newX-oldX == 2){

            // delete old empty piece
            delete board[oldY][5];
            // move right Rook
            board[oldY][5] = board[oldY][7];
            board[oldY][7] = new Piece();
            lmShortCastling = true;

        }


        // detect long castling
        else if (board[oldY][oldX]->getType() == 'k' && newX-oldX == -2){

            // delete old empty piece
            delete board[oldY][3];
            // move right Rook
            board[oldY][3] = board[oldY][0];
            board[oldY][0] = new Piece();
            lmLongCastling = true;
        }




        // for the piece/empty piece at new position
        // store in vector if catpure
        if (board[newY][newX]->isAlive()){
            capturedPieces.push_back(board[newY][newX]);
        }
        else {
            // delete old piece
            delete board[newY][newX];
        }


        // replace new square with old piece
        board[newY][newX] = board[oldY][oldX];


        // kill old piece position
        board[oldY][oldX] = new Piece();


        // increment moves/turn
        ++moveCount;

        // set flag "piece notMoved" to false, for castling info
        board[newY][newX]->hasMoved();



        bool lmCheck = testCheck();
        bool lmNoMoves = !playerCanMove();

        lastMove = LastMove(oldX, oldY, newX, newY, lmType, lmCapt, lmProm,
                lmCheck, lmNoMoves, lmShortCastling, lmLongCastling, lmMoveColor);


        // print move list

        if (!silent){
            if (!atMove())
                cout << std::setw(5) << std::string(std::to_string(moveCount / 2 + moveCount % 2) + ". ");
            cout << lastMove << std::flush;
            if (atMove())
                cout << endl;
            else
                cout << " ";
        }




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

bool Board::getPlayerAI(bool player) const {
    return players[player].isAI();
}
