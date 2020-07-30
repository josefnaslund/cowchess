#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "GUI.h"
#include "constants.h"
#include "Piece.h"
#include "text_turn.xpm"
#include "text_check.xpm"
#include "text_checkmate.xpm"
#include "text_draw.xpm"
#include "knight_w.xpm"
#include "rook_w.xpm"
#include "queen_w.xpm"
#include "bishop_w.xpm"
#include "knight_b.xpm"
#include "rook_b.xpm"
#include "queen_b.xpm"
#include "bishop_b.xpm"

using std::cout, std::endl;

GUI::GUI(Board* _gameBoard)
{
    window = nullptr;
    renderer = nullptr;
    texture = nullptr;
    images = std::vector<std::pair<const char**, SDL_Texture*>> {};
    surface = nullptr;
    gameBoard = _gameBoard;
    turnTexture = nullptr;
    checkTexture = nullptr;
    promotionTextureWhite = nullptr;
    promotionTextureBlack = nullptr;
    mouse = nullptr;
    touch = nullptr;
}

GUI::~GUI(){
    for (auto p : images){
        SDL_DestroyTexture(p.second);
    }

    images.clear(); // remove previous content of vector
    SDL_DestroyTexture(turnTexture);
    SDL_DestroyTexture(checkTexture);

    for (int i = 0; i != 4; ++i){
        if (promotionTextureWhite)
            SDL_DestroyTexture(promotionTextureWhite[i]);
        if (promotionTextureBlack)
            SDL_DestroyTexture(promotionTextureBlack[i]);
    }

    delete[] promotionTextureWhite;
    delete[] promotionTextureBlack;


}

bool GUI::init(){
    window = SDL_CreateWindow
        ("Chess Program", SDL_WINDOWPOS_UNDEFINED,
         SDL_WINDOWPOS_UNDEFINED,
         SCREEN_WIDTH,
         SCREEN_HEIGHT,
         SDL_WINDOW_SHOWN
        );

    if (window != nullptr) {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    }
    else {
        std::cerr << "Error window: " << SDL_GetError();
    }

    if (renderer == nullptr) {
        std::cerr << "Error renderer: " << SDL_GetError();
    }


    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
        std::cerr << "Failed to init SDL_image (png)\n";
    }

    if (IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG){
        std::cerr << "Failed to init SDL_image (jpg)\n";
    }



    return renderer != nullptr;
}

void GUI::setMouse(Mouse* _mouse){
    mouse = _mouse;
}

void GUI::setTouch(Touch* _touch){
    touch = _touch;
}

void GUI::drawBoard(){

    // draw background color
    SDL_SetRenderDrawColor(renderer, 170, 120, 50, 255);
    SDL_RenderClear(renderer);

    // a rectangle shape
    SDL_Rect r;

    // draw the chess board
    for (int row = 0; row != 8; ++row){
        for (int col = 0; col != 8; ++col){

            r.x = LEFT_MARGIN + col * SQUARE_SIZE;
            r.y = TOP_MARGIN + row * SQUARE_SIZE;
            r.w = SQUARE_SIZE;
            r.h = SQUARE_SIZE;

            if (!((row + col) % 2)){
                // set to light color
                SDL_SetRenderDrawColor( renderer, 200, 200, 200, 255 );
            }

            else {
                // set to dark color
                SDL_SetRenderDrawColor( renderer, 50, 50, 50, 255 );
            }

            // draw a chess square
            SDL_RenderFillRect( renderer, &r );
        }
    }

    drawTurn();
}


void GUI::drawTextCheck(){
    if (checkTexture == nullptr){
        loadTexture(text_check_xpm);
        checkTexture = texture;
    }

    SDL_Rect r; 
    r.x = 27;  
    r.y = 200; 
    r.w = 74; 
    r.h = 32;

    SDL_RenderCopy(renderer, checkTexture, nullptr, &r);

}

void GUI::drawTextMate(){
    loadTexture(text_checkmate_xpm);
    SDL_Texture* checkmate = texture;

    SDL_Rect r; 
    r.x = LEFT_MARGIN + 8 * SQUARE_SIZE / 2 - 190 / 2;   // == 225
    r.y = TOP_MARGIN + 8 * SQUARE_SIZE / 2 - 45/2;  // == 217
    r.w = 190; 
    r.h = 45; 

    SDL_RenderCopy(renderer, checkmate, nullptr, &r);

    SDL_DestroyTexture(checkmate);
}

void GUI::drawTextDraw(){
    loadTexture(text_draw_xpm);
    SDL_Texture* checkmate = texture;

    SDL_Rect r; 
    r.x = LEFT_MARGIN + 8 * SQUARE_SIZE / 2 - 85 / 2; 
    r.y = TOP_MARGIN + 8 * SQUARE_SIZE / 2 - 45/2;  // == 217
    r.w = 85; 
    r.h = 45; 

    SDL_RenderCopy(renderer, checkmate, nullptr, &r);

    SDL_DestroyTexture(checkmate);
}

void GUI::drawTurn(){

    // draw turn text image
    if (turnTexture == nullptr){
        loadTexture(text_turn_xpm);
        turnTexture = texture;
    }

    SDL_Rect r; 
    r.x = 34;  
    r.y = 55; 
    r.w = 50; 
    r.h = 17; 

    SDL_RenderCopy(renderer, turnTexture, nullptr, &r);

    // draw squares with turn info
    // draw border around turn-square
    r.x = LEFT_MARGIN / 2 - SQUARE_SIZE / 2 - 1;
    r.y = TOP_MARGIN * 2 - 1;
    r.w = SQUARE_SIZE + 2;
    r.h = SQUARE_SIZE + 2;

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderFillRect( renderer, &r);

    // draw turn of player
    r.x = LEFT_MARGIN / 2 - SQUARE_SIZE / 2;
    r.y = TOP_MARGIN * 2;
    r.w = SQUARE_SIZE;
    r.h = SQUARE_SIZE;

    if (gameBoard->atMove()){
        // set to light color
        SDL_SetRenderDrawColor( renderer, 200, 200, 200, 255 );
    }

    else {
        // set to dark color
        SDL_SetRenderDrawColor( renderer, 50, 50, 50, 255 );
    }

    SDL_RenderFillRect( renderer, &r);
}



void GUI::drawAIstatus(){

    // draw text AI
    // if (turnTexture == NULL){
    //     loadTexture(text_turn_xpm);
    //     turnTexture = texture;
    // }

    SDL_Rect r; 

    // r.x = 34;  
    // r.y = 55; 
    // r.w = 50; 
    // r.h = 17; 

    // SDL_RenderCopy(renderer, turnTexture, NULL, &r);


    // draw two borders around AI info

    // draw first border
    r.x = LEFT_MARGIN / 4 - SQUARE_SIZE / 4 - 1;
    r.y = TOP_MARGIN + SQUARE_SIZE * 7.5 - 1;
    r.w = SQUARE_SIZE / 2 + 2;
    r.h = SQUARE_SIZE / 2 + 2;

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderFillRect( renderer, &r);

    // draw second border
    r.x = LEFT_MARGIN / 4 * 3 - SQUARE_SIZE / 4 - 1;
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderFillRect( renderer, &r);


    // draw player 1 info
    r.x = LEFT_MARGIN / 4 - SQUARE_SIZE / 4;
    r.y = TOP_MARGIN + SQUARE_SIZE * 7.5;
    r.w = SQUARE_SIZE / 2;
    r.h = SQUARE_SIZE / 2;

    // draw brighter white color if player is ai
    if (gameBoard->getPlayerAI(true)){
        // set to light color
        SDL_SetRenderDrawColor( renderer, 200, 200, 200, 255 );
    }

    // draw darker white color
    else {

        SDL_SetRenderDrawColor( renderer, 125, 125, 125, 255 );
    }

    SDL_RenderFillRect( renderer, &r);

    r.x = LEFT_MARGIN / 4 * 3 - SQUARE_SIZE / 4;
    r.y = TOP_MARGIN + SQUARE_SIZE * 7.5;

    // draw darker
    if (gameBoard->getPlayerAI(false)){
        // set to light color
        SDL_SetRenderDrawColor( renderer, 50, 50, 50, 255 );
    }


    // draw brighter color
    else {
        // set to dark color
        SDL_SetRenderDrawColor( renderer, 125, 125, 125, 255 );
    }

    SDL_RenderFillRect( renderer, &r);
}


void GUI::drawCapturedPieces(){

    SDL_Rect r;
    r.h = SQUARE_SIZE / 2;
    r.w = SQUARE_SIZE / 2;
    r.y = TOP_MARGIN;
    int imgIndex;

    // draw both colors, iterate through vector twice
    for (int i = 0; i != 2; ++i){

        r.x = LEFT_MARGIN + SQUARE_SIZE * 8.2;
        int count = 0;

        for (auto p : gameBoard->getCapturedPieces()){

            if (i != p->isWhite()){
                imgIndex = findImage(p->getImage());
                ++count;


                // if image exists
                if (imgIndex != -1 && images[imgIndex].second) {
                    SDL_RenderCopy(renderer, images[imgIndex].second, nullptr, &r);
                }

                // if no img with that name, draw red square
                else {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderFillRect( renderer, &r );
                    std::cerr << "Error: can't find image of captured piece\n";
                }
                r.x += SQUARE_SIZE / 3;

                if (count == 5){
                    r.x = LEFT_MARGIN + SQUARE_SIZE * 8.2;
                    r.y += SQUARE_SIZE / 2;
                    count = 0;
                }
            }
        }
        r.y = TOP_MARGIN + SQUARE_SIZE * 6;
    }
}

void GUI::drawPromotionPieces(bool color){

    SDL_Rect r;

    // border
    r.x = LEFT_MARGIN / 2 - SQUARE_SIZE / 2 - 1;
    r.y = TOP_MARGIN + SQUARE_SIZE * 2 - 1;
    r.w = SQUARE_SIZE + 2;
    r.h = SQUARE_SIZE * 4 + 2;
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderFillRect( renderer, &r);

    // area
    r.x = LEFT_MARGIN / 2 - SQUARE_SIZE / 2;
    r.y = TOP_MARGIN + SQUARE_SIZE * 2;
    r.w = SQUARE_SIZE;
    r.h = SQUARE_SIZE * 4;
    SDL_SetRenderDrawColor( renderer, 125, 125, 125, 255 );
    SDL_RenderFillRect( renderer, &r);


    // load white images to texture
    if (color && !promotionTextureWhite){
        promotionTextureWhite = new SDL_Texture*[4];
        loadTexture(knight_w_xpm);
        promotionTextureWhite[0] = texture;
        loadTexture(rook_w_xpm);
        promotionTextureWhite[1] = texture;
        loadTexture(bishop_w_xpm);
        promotionTextureWhite[2] = texture;
        loadTexture(queen_w_xpm);
        promotionTextureWhite[3] = texture;
        texture = nullptr;
    }

    // load black images to texture
    if (!color && !promotionTextureBlack){
        promotionTextureBlack = new SDL_Texture*[4];
        loadTexture(knight_b_xpm);
        promotionTextureBlack[0] = texture;
        loadTexture(rook_b_xpm);
        promotionTextureBlack[1] = texture;
        loadTexture(bishop_b_xpm);
        promotionTextureBlack[2] = texture;
        loadTexture(queen_b_xpm);
        promotionTextureBlack[3] = texture;
        texture = nullptr;
    }

    // draw all pieces
    r.x = LEFT_MARGIN / 2 - SQUARE_SIZE / 2;
    r.y = TOP_MARGIN + SQUARE_SIZE * 2;
    r.w = SQUARE_SIZE;
    r.h = SQUARE_SIZE;

    for (int i = 0; i != 4; ++i){
        if (color && promotionTextureWhite) {
            SDL_RenderCopy(renderer, promotionTextureWhite[i], nullptr, &r);
        }

        else if (!color && promotionTextureBlack) {
            SDL_RenderCopy(renderer, promotionTextureBlack[i], nullptr, &r);
        }

        // if no img with that name, draw red square
        else {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect( renderer, &r );
            std::cerr << "Error: can't find image\n";
        }

        r.y = TOP_MARGIN + SQUARE_SIZE * 2 + SQUARE_SIZE * i + SQUARE_SIZE;

    }
}



void GUI::loadImages(){
    Piece*** board = gameBoard->getBoard();

    for (int row = 0; row != 8; ++row){
        for (int col = 0; col != 8; ++col){
            if (board[row][col]->isAlive()){

                bool found = false;
                for (auto p : images){
                    if (board[row][col]->getImage() == p.first){
                        found = true;
                        break;
                    }
                }

                if (!found){
                    loadTexture(board[row][col]->getImage());
                    if (texture){
                        std::pair<const char**, SDL_Texture*> newPair 
                        {
                            board[row][col]->getImage(),
                                texture

                        };
                        images.push_back(newPair);
                        texture = nullptr;
                    }
                }

            }
        }
    }
}



int GUI::findImage(const char** img){
    for (uint i = 0; i != images.size(); ++i){
        if (images[i].first == img){
            return i;
        }
    }
    return -1;
}



void GUI::drawPieces(){
    Piece*** board = gameBoard->getBoard();

    // will be called once on startup, to collect images to vector
    if (images.empty()){
        // std::cout << "vector 'images' is empty\n";
        loadImages();
        // std::cout << "There are now " << images.size() << " images in vector\n";
    }

    // to draw pieces
    SDL_Rect r;

    for (int row = 0; row != 8; ++row){
        for (int col = 0; col != 8; ++col){
            if (board[row][col]->isAlive()){

                r.x = LEFT_MARGIN + col * SQUARE_SIZE;
                r.y = TOP_MARGIN + (7 - row) * SQUARE_SIZE;
                r.w = SQUARE_SIZE;
                r.h = SQUARE_SIZE;
                int index = findImage(board[row][col]->getImage());

                // if image exists
                if (index != -1 && images[index].second) {
                    SDL_RenderCopy(renderer, images[index].second, nullptr, &r);
                }

                // if no img with that name, draw red square
                else {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderFillRect( renderer, &r );
                    std::cerr << "Error: can't find image\n";
                }
            }
        }
    }
}

bool GUI::loadTexture(const char** img){
    texture = nullptr;

    surface = IMG_ReadXPMFromArray((char**)img);

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture){
        std::cerr << "Can't load texture: " << img << std::endl;
        return false;
    }
    SDL_FreeSurface(surface);
    surface = nullptr;
    return true;
}

void GUI::drawCurrentPieceMouse(){
    // absolute position of locked piece
    int tempX = mouse->getAbsoluteLockedPosition().first;
    int tempY = mouse->getAbsoluteLockedPosition().second;

    // the position within the square
    int diffX =  (tempX - LEFT_MARGIN) % SQUARE_SIZE;
    int diffY =  (tempY - TOP_MARGIN) % SQUARE_SIZE;

    // position of upper left corner of square
    int squareX = tempX - diffX;
    int squareY = tempY - diffY;

    SDL_Rect r;
    r.x = squareX;
    r.y = squareY;
    r.h= SQUARE_SIZE;
    r.w = SQUARE_SIZE;

    // draw highlighted square to cover piece square
    SDL_SetRenderDrawColor(renderer, 100, 50, 50, 200);
    SDL_RenderFillRect( renderer, &r );

    
    // draw highlighted square to cover current square
    tempX = mouse->getAbsoluteCurrentPosition().first;
    tempY = mouse->getAbsoluteCurrentPosition().second;
    if (
            tempX > LEFT_MARGIN && 
            tempX < LEFT_MARGIN + SQUARE_SIZE * 8 &&
            tempY > TOP_MARGIN &&
            tempY < TOP_MARGIN + SQUARE_SIZE * 8
            ){
        r.x = tempX - ((tempX - LEFT_MARGIN) % SQUARE_SIZE);
        r.y = tempY - ((tempY - TOP_MARGIN) % SQUARE_SIZE);


        SDL_SetRenderDrawColor(renderer, 150, 50, 50, 200);
        SDL_RenderFillRect( renderer, &r );
    }



    // draw piece at mouse position
    r.x = tempX - diffX;
    r.y = tempY - diffY;
    int tempIndex = findImage(
            gameBoard->getBoard()[mouse->getPosY()][mouse->getPosX()]->getImage()
            );

    if (tempIndex != -1){
        SDL_RenderCopy(renderer, images[tempIndex].second, nullptr, &r);

    }
}


void GUI::drawCurrentPieceTouch(){
    // absolute position of locked piece
    int tempX = touch->getAbsoluteLockedPosition().first;
    int tempY = touch->getAbsoluteLockedPosition().second;

    // the position within the square
    int diffX =  (tempX - LEFT_MARGIN) % SQUARE_SIZE;
    int diffY =  (tempY - TOP_MARGIN) % SQUARE_SIZE;

    // position of upper left corner of square
    int squareX = tempX - diffX;
    int squareY = tempY - diffY;

    SDL_Rect r;
    r.x = squareX;
    r.y = squareY;
    r.h = SQUARE_SIZE;
    r.w = SQUARE_SIZE;

    // draw square to cover piece square
    SDL_SetRenderDrawColor(renderer, 100, 50, 50, 200);
    SDL_RenderFillRect( renderer, &r );


    // draw highlighted square to cover current square
    tempX = touch->getAbsoluteCurrentPosition().first;
    tempY = touch->getAbsoluteCurrentPosition().second;
    if (

            tempX > LEFT_MARGIN && 
            tempX < LEFT_MARGIN + SQUARE_SIZE * 8 &&
            tempY > TOP_MARGIN &&
            tempY < TOP_MARGIN + SQUARE_SIZE * 8
            ){
        r.x = tempX - ((tempX - LEFT_MARGIN) % SQUARE_SIZE);
        r.y = tempY - ((tempY - TOP_MARGIN) % SQUARE_SIZE);


        SDL_SetRenderDrawColor(renderer, 150, 50, 50, 200);
        SDL_RenderFillRect( renderer, &r );
    }


    // draw piece at mouse position
    r.x = tempX - diffX;
    r.y = tempY - diffY;
    int tempIndex = findImage(
            gameBoard->getBoard()[touch->getPosY()][touch->getPosX()]->getImage()
            );

    if (tempIndex != -1){
        SDL_RenderCopy(renderer, images[tempIndex].second, nullptr, &r);
    }
}




void GUI::drawLastMove() {
    LastMove lm = gameBoard->getLastMove();
    if (lm.getOldX() != -1) {
        SDL_Rect r;
        r.w = 10;
        r.h = 10;
        SDL_SetRenderDrawColor(renderer, 240, 60, 0, 10);

        int x1 = LEFT_MARGIN + SQUARE_SIZE * lm.getOldX() + SQUARE_SIZE / 2 - 5;
        int x2 = LEFT_MARGIN + SQUARE_SIZE * lm.getNewX() + SQUARE_SIZE / 2 - 5;
        int y1 = TOP_MARGIN + SQUARE_SIZE * (7 - lm.getOldY()) + SQUARE_SIZE / 2 - 5;
        int y2 = TOP_MARGIN + SQUARE_SIZE * (7 - lm.getNewY()) + SQUARE_SIZE / 2 - 5;

        if (x1 == x2){
            while (y1 != y2) {
                r.x = x1;
                r.y = y1;

                SDL_RenderFillRect(renderer, &r);

                // increment or decrement y1
                y1 = y1 < y2 ? y1 + 1 : y1 - 1;
            }
        }
        else {
            SDL_SetRenderDrawColor(renderer, 240, 60, 0, 20);

            int dx = x2 - x1;
            int dy = y2 - y1;
            int x = x1;

            while (x != x2) {
                r.x = x;
                r.y = y1 + dy * (x - x1) / dx;

                SDL_RenderFillRect(renderer, &r);

                // increment or decrement x
                x = x < x2 ? x + 1 : x - 1;
            }
        }
    }
}

void GUI::update(){

    // draw the board
    drawBoard();

    // draw last move line
    drawLastMove();


    // draw the pieces
    drawPieces();
    if (gameBoard->getLastMove().isCheck()){
        if (gameBoard->getLastMove().noMoves()){
            drawTextMate();
        }
        else {
            drawTextCheck();
        }
    }
    else if (gameBoard->getLastMove().noMoves()){
        drawTextDraw();
    }


    // draw promotion alternatives
    if (gameBoard->isPromotion()){
        drawPromotionPieces(gameBoard->atMove());
    }

    // draw AI on/off info box
    drawAIstatus();

    // draw captured pieces
    drawCapturedPieces();


    // draw a moving piece
    if (mouse->isLocked()){
        drawCurrentPieceMouse();
    }

    else if (touch->isLocked()){
        drawCurrentPieceTouch();
    }

    // done - lets present to screen
    SDL_RenderPresent(renderer);
}
