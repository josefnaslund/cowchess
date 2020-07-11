#include <iostream>
#include "Mouse.h"
#include "constants.h"
#include "Piece.h"
#include "Player.h"

using std::cout; 
using std::endl;

Mouse::Mouse(Board* _gameBoard){
    posX = 0;
    posY = 0;
    gameBoard = _gameBoard;
}

void Mouse::setPosX(int _x){
    posX = _x;
}

void Mouse::setPosY(int _y){
    posY = _y;
}


bool Mouse::getIndexPos(const int& guiX, const int& guiY, int& arrX, int& arrY){

    if (guiX <= LEFT_MARGIN || guiX >= LEFT_MARGIN + 8 * SQUARE_SIZE ||
            guiY <= TOP_MARGIN || guiY >= TOP_MARGIN + 8 * SQUARE_SIZE){
        return false;
    }

    //cout << "Mouse - Piece at pos: " << guiX << "," << guiY << " : ";


    // chess position x
    arrX = (guiX - LEFT_MARGIN) / 50;
    //cout << (char)(65 + arrX);

    // chess position y
    arrY = (7 - (guiY - TOP_MARGIN) / 50);

    //cout << arrY + 1 << endl;


    return true;

}

bool Mouse::mouseEvents(SDL_Event& e, Board& board){

    bool moveMade = false;

    // to prevent mouse buttons other than left to interfere
    if (e.button.button != SDL_BUTTON_LEFT){
        ; // do nothing
    }

    // if left button push
    else if (e.type == SDL_MOUSEBUTTONDOWN){
        SDL_ShowCursor(SDL_ENABLE);
        // cout << "Mouse at: " << e.button.x << ", " << e.button.y << endl;

        // set to "not locked"
        setLocked(false);

        int arrX = -1, arrY = -1;

        Piece* clickedPiece = NULL;

        if (getIndexPos(e.button.x, e.button.y, arrX, arrY)){
            //cout << "Mouse: arrpos: [" << arrY << "][" << arrX << "]\n";
            clickedPiece = board.getPieceAt(arrX, arrY);
        }

        // if there is a piece at clicked pos
        if (clickedPiece && clickedPiece->isAlive()){

            setLocked(true);
            if (arrX == -1 || arrY == -1)
                std::cerr << "__This should not happen __" << arrX << " " << arrY << "\n";

            setPosX(arrX);
            setPosY(arrY);
        }

        // no piece clicked, but clicked at GUI AI select square left
        if (!clickedPiece && 
                e.button.x >= (LEFT_MARGIN / 4 - SQUARE_SIZE / 4) && 
                e.button.x <= (LEFT_MARGIN / 4 + SQUARE_SIZE / 4) && 
                e.button.y >= (TOP_MARGIN + SQUARE_SIZE * 5) && 
                e.button.y <= (TOP_MARGIN + SQUARE_SIZE * 5 + SQUARE_SIZE / 2)){
            Player* players = gameBoard->getPlayers();
            players[1].setAI(!players[1].isAI());
        }
        // ... or select square right
        else if (!clickedPiece && 
                e.button.x >= (LEFT_MARGIN / 4 * 3 - SQUARE_SIZE / 4) && 
                e.button.x <= (LEFT_MARGIN / 4 * 3 + SQUARE_SIZE / 4) && 
                e.button.y >= (TOP_MARGIN + SQUARE_SIZE * 5) && 
                e.button.y <= (TOP_MARGIN + SQUARE_SIZE * 5 + SQUARE_SIZE / 2)){
            Player* players = gameBoard->getPlayers();
            players[0].setAI(!players[0].isAI());
        }





    }

    // if left button release
    else if (e.type == SDL_MOUSEBUTTONUP){
        // SDL_Delay(300);

        // if user is grabbing a piece and releasing the button
        if (isLocked()){

            int arrX = -1, arrY = -1;
            if (getIndexPos(e.button.x, e.button.y, arrX, arrY)){
                if (arrX != getPosX() || arrY != getPosY()){

                    if ( board.movePiece( getPosX(),
                                getPosY(),
                                arrX,
                                arrY))
                    {
                        moveMade = true;

                    }
                }
            }

        }
    }

    return moveMade;
}

