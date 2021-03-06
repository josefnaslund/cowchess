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
    locked = false;
    absoluteLockedPosition = std::make_pair(0, 0);
    absoluteCurrentPosition = std::make_pair(0, 0);
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
    arrX = (guiX - LEFT_MARGIN) / SQUARE_SIZE;
    //cout << (char)(65 + arrX);

    // chess position y
    arrY = (7 - (guiY - TOP_MARGIN) / SQUARE_SIZE);

    //cout << arrY + 1 << endl;


    return true;

}

bool Mouse::mouseEvents(SDL_Event& e, Board& board){

    bool moveMade = false;

    absoluteCurrentPosition.first = e.button.x;
    absoluteCurrentPosition.second = e.button.y;

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

        Piece* clickedPiece = nullptr;

        if (getIndexPos(e.button.x, e.button.y, arrX, arrY)){
            //cout << "Mouse: arrpos: [" << arrY << "][" << arrX << "]\n";
            clickedPiece = board.getPieceAt(arrX, arrY);
        }

        // if there is a piece at clicked pos
        if (clickedPiece && clickedPiece->isAlive() && !gameBoard->getPlayers()[gameBoard->atMove()].isAI()){

            setLocked(true);
            if (arrX == -1 || arrY == -1)
                std::cerr << "__This should not happen __" << arrX << " " << arrY << "\n";

            setPosX(arrX);
            setPosY(arrY);
            absoluteLockedPosition.first = e.button.x;
            absoluteLockedPosition.second = e.button.y;
        }

        // no piece clicked, but clicked at GUI AI select square left (White player)
        if (!clickedPiece && 
                e.button.x >= (LEFT_MARGIN / 4 - SQUARE_SIZE / 4) && 
                e.button.x <= (LEFT_MARGIN / 4 + SQUARE_SIZE / 4) && 
                e.button.y >= (TOP_MARGIN + SQUARE_SIZE * 7.5) && 
                e.button.y <= (TOP_MARGIN + SQUARE_SIZE * 7.5 + SQUARE_SIZE / 2)){
            Player* players = gameBoard->getPlayers();
            players[1].setAI(!players[1].isAI());
        }
        // ... or select AI square right (Black player)
        else if (!clickedPiece && 
                e.button.x >= (LEFT_MARGIN / 4 * 3 - SQUARE_SIZE / 4) && 
                e.button.x <= (LEFT_MARGIN / 4 * 3 + SQUARE_SIZE / 4) && 
                e.button.y >= (TOP_MARGIN + SQUARE_SIZE * 7.5) && 
                e.button.y <= (TOP_MARGIN + SQUARE_SIZE * 7.5 + SQUARE_SIZE / 2)){
            Player* players = gameBoard->getPlayers();
            players[0].setAI(!players[0].isAI());
        }

        // if promotion, choose among promotion squares
        else if (!clickedPiece && gameBoard->isPromotion()){
            bool buttonPress = false;
            if (
                    e.button.x >= LEFT_MARGIN / 2 - SQUARE_SIZE / 2 &&
                    e.button.x < LEFT_MARGIN / 2 + SQUARE_SIZE / 2
               ){
                // knight pos.
                if (
                        e.button.y >= TOP_MARGIN + SQUARE_SIZE * 2 && 
                        e.button.y < TOP_MARGIN + SQUARE_SIZE * 3
                   )
                {
                    gameBoard->setPromotionChar('n');
                    buttonPress = true;
                }

                // rook pos.
                else if (
                        e.button.y >= TOP_MARGIN + SQUARE_SIZE * 3 && 
                        e.button.y < TOP_MARGIN + SQUARE_SIZE * 4

                        )
                {
                    gameBoard->setPromotionChar('r');
                    buttonPress = true;
                }

                // bishop pos.
                else if (
                        e.button.y >= TOP_MARGIN + SQUARE_SIZE * 4 && 
                        e.button.y < TOP_MARGIN + SQUARE_SIZE * 5
                        )
                {
                    gameBoard->setPromotionChar('b');
                    buttonPress = true;
                }

                // queen pos.
                else if (
                        e.button.y >= TOP_MARGIN + SQUARE_SIZE * 5 && 
                        e.button.y < TOP_MARGIN + SQUARE_SIZE * 6
                        )
                {
                    gameBoard->setPromotionChar('q');
                    buttonPress = true;
                }

                if (buttonPress){
                    if (gameBoard->movePiece(
                                gameBoard->getPromotionOldX(),
                                gameBoard->getPromotionOldY(),
                                gameBoard->getPromotionNewX(),
                                gameBoard->getPromotionNewY())
                       )
                    {
                        moveMade = true;
                    }
                }
            }
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
            setLocked(false);
        }
    }

    return moveMade;
}

