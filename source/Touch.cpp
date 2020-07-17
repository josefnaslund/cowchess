#include <iostream>
#include "Touch.h"
#include "constants.h"
#include "Piece.h"
#include "Player.h"

using std::cout; 
using std::endl;

Touch::Touch(Board* _gameBoard){
    posX = 0;
    posY = 0;
    gameBoard = _gameBoard;
}

void Touch::setPosX(int _x){
    posX = _x;
}

void Touch::setPosY(int _y){
    posY = _y;
}


bool Touch::getIndexPos(const int& guiX, const int& guiY, int& arrX, int& arrY){

    if (guiX <= LEFT_MARGIN || guiX >= LEFT_MARGIN + 8 * SQUARE_SIZE ||
            guiY <= TOP_MARGIN || guiY >= TOP_MARGIN + 8 * SQUARE_SIZE){
        return false;
    }

    // cout << "Touch - Piece at pos: " << guiX << "," << guiY << " : ";


    // chess position x
    arrX = (guiX - LEFT_MARGIN) / 50;
    //cout << (char)(65 + arrX);

    // chess position y
    arrY = (7 - (guiY - TOP_MARGIN) / 50);

    //cout << arrY + 1 << endl;


    return true;

}

bool Touch::touchEvents(SDL_Event& fe, Board& board){
    SDL_ShowCursor(SDL_DISABLE);
    bool moveMade = false;


    // if finger down
    if (fe.type == SDL_FINGERDOWN){
        // cout << "SDL_FINGERDOWN\n";
        // cout << "Touch at: " << fe.tfinger.x * SCREEN_WIDTH << ", " << fe.tfinger.y * SCREEN_HEIGHT << endl;

        // set to "not locked"
        setLocked(false);

        int arrX = -1, arrY = -1;

        Piece* clickedPiece = NULL;

        if (getIndexPos(fe.tfinger.x * SCREEN_WIDTH, fe.tfinger.y * SCREEN_HEIGHT, arrX, arrY)){
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
                fe.tfinger.x * SCREEN_WIDTH >= (LEFT_MARGIN / 4 - SQUARE_SIZE / 4) && 
                fe.tfinger.x * SCREEN_WIDTH <= (LEFT_MARGIN / 4 + SQUARE_SIZE / 4) && 
                fe.tfinger.y * SCREEN_HEIGHT >= (TOP_MARGIN + SQUARE_SIZE * 5) && 
                fe.tfinger.y * SCREEN_HEIGHT <= (TOP_MARGIN + SQUARE_SIZE * 5 + SQUARE_SIZE / 2)){
            Player* players = gameBoard->getPlayers();
            players[1].setAI(!players[1].isAI());
        }
        // ... or select square right
        else if (!clickedPiece && 
                fe.tfinger.x * SCREEN_WIDTH >= (LEFT_MARGIN / 4 * 3 - SQUARE_SIZE / 4) && 
                fe.tfinger.x * SCREEN_WIDTH <= (LEFT_MARGIN / 4 * 3 + SQUARE_SIZE / 4) && 
                fe.tfinger.y * SCREEN_HEIGHT >= (TOP_MARGIN + SQUARE_SIZE * 5) && 
                fe.tfinger.y * SCREEN_HEIGHT <= (TOP_MARGIN + SQUARE_SIZE * 5 + SQUARE_SIZE / 2)){
            Player* players = gameBoard->getPlayers();
            players[0].setAI(!players[0].isAI());
        }

        // if promotion, choose among promotion squares
        else if (!clickedPiece && gameBoard->isPromotion()){
            bool buttonPress = false;
            if (
                    fe.button.x >= LEFT_MARGIN / 2 - SQUARE_SIZE / 2 &&
                    fe.button.x < LEFT_MARGIN / 2 + SQUARE_SIZE / 2
               ){
                // knight pos.
                if (
                        fe.button.y >= TOP_MARGIN + SQUARE_SIZE * 2 && 
                        fe.button.y < TOP_MARGIN + SQUARE_SIZE * 3
                   )
                {
                    gameBoard->setPromotionChar('n');
                    buttonPress = true;
                }

                // rook pos.
                else if (
                        fe.button.y >= TOP_MARGIN + SQUARE_SIZE * 3 && 
                        fe.button.y < TOP_MARGIN + SQUARE_SIZE * 4

                        )
                {
                    gameBoard->setPromotionChar('r');
                    buttonPress = true;
                }

                // queen pos.
                else if (
                        fe.button.y >= TOP_MARGIN + SQUARE_SIZE * 4 && 
                        fe.button.y < TOP_MARGIN + SQUARE_SIZE * 5
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
    else if (fe.type == SDL_FINGERUP){
        // cout << "SDL_FINGERUP\n";
        // SDL_Delay(300);

        // if user is grabbing a piece and releasing the button
        if (isLocked()){

            int arrX = -1, arrY = -1;
            if (getIndexPos(fe.tfinger.x * SCREEN_WIDTH, fe.tfinger.y * SCREEN_HEIGHT, arrX, arrY)){
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

