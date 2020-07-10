#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cstring>
#include <iostream>
#include "GUI.h"
#include "constants.h"
#include "Piece.h"
#include "text_turn.xpm"
#include "text_check.xpm"
#include "text_checkmate.xpm"
#include "text_draw.xpm"

using std::cout; 
using std::endl;

GUI::GUI(Board* _gameBoard)
{
    window = NULL;
    renderer = NULL;
    texture = NULL;
    images = std::vector<std::pair<const char**, SDL_Texture*>> {};
    surface = NULL;
    gameBoard = _gameBoard;
    turnTexture = NULL;
    checkTexture = NULL;
    

}

GUI::~GUI(){
        for (auto p : images){
                SDL_DestroyTexture(p.second);
        }

        images.clear(); // remove previous content of vector
        SDL_DestroyTexture(turnTexture);
        SDL_DestroyTexture(checkTexture);
}

bool GUI::init(){
    window = SDL_CreateWindow
        ("Chess Program", SDL_WINDOWPOS_UNDEFINED,
         SDL_WINDOWPOS_UNDEFINED,
         SCREEN_WIDTH,
         SCREEN_HEIGHT,
         SDL_WINDOW_SHOWN
        );

    if (window != NULL)
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    else 
        std::cerr << "Error window: " << SDL_GetError();

    if (renderer == NULL) 
       std::cerr << "Error renderer: " <<  SDL_GetError();
    

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
        std::cerr << "Failed to init SDL_image (png)\n";
    }

    if (IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG){
        std::cerr << "Failed to init SDL_image (jpg)\n";
    }

    return renderer != NULL;
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
    if (checkTexture == NULL){
        loadTexture(text_check_xpm);
        checkTexture = texture;
    }

    SDL_Rect r; 
    r.x = 27;  
    r.y = 200; 
    r.w = 74; 
    r.h = 32; 

    SDL_RenderCopy(renderer, checkTexture, NULL, &r);

}

void GUI::drawTextMate(){
    loadTexture(text_checkmate_xpm);
    SDL_Texture* checkmate = texture;

    SDL_Rect r; 
    r.x = LEFT_MARGIN + 8 * SQUARE_SIZE / 2 - 190 / 2;   // == 225
    r.y = TOP_MARGIN + 8 * SQUARE_SIZE / 2 - 45/2;  // == 217
    r.w = 190; 
    r.h = 45; 

    SDL_RenderCopy(renderer, checkmate, NULL, &r);

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

    SDL_RenderCopy(renderer, checkmate, NULL, &r);

    SDL_DestroyTexture(checkmate);

}

void GUI::drawTurn(){

    // draw turn text image
    if (turnTexture == NULL){
        loadTexture(text_turn_xpm);
        turnTexture = texture;
    }

    SDL_Rect r; 
    r.x = 34;  
    r.y = 55; 
    r.w = 50; 
    r.h = 17; 

    SDL_RenderCopy(renderer, turnTexture, NULL, &r);

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
    r.y = TOP_MARGIN + SQUARE_SIZE * 5 - 1;
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
    r.y = TOP_MARGIN + SQUARE_SIZE * 5;
    r.w = SQUARE_SIZE / 2;
    r.h = SQUARE_SIZE / 2;

    // draw brighter white color if player is ai
    if (gameBoard->getPlayerAI(1)){
        // set to light color
        SDL_SetRenderDrawColor( renderer, 200, 200, 200, 255 );
    }

    // draw darker white color
    else {
            
        SDL_SetRenderDrawColor( renderer, 125, 125, 125, 255 );
    }

    SDL_RenderFillRect( renderer, &r);

    r.x = LEFT_MARGIN / 4 * 3 - SQUARE_SIZE / 4;
    r.y = TOP_MARGIN + SQUARE_SIZE * 5;

    // draw darker
    if (gameBoard->getPlayerAI(0)){
        // set to light color
        SDL_SetRenderDrawColor( renderer, 50, 50, 50, 255 );
    }


    // draw brigher
    else {
        // set to dark color
        SDL_SetRenderDrawColor( renderer, 125, 125, 125, 255 );
    }

    SDL_RenderFillRect( renderer, &r);
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
                        texture = NULL;
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
    texture = NULL;

    surface = IMG_ReadXPMFromArray((char**)img);

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture){
        std::cerr << "Can't load texture: " << img << std::endl;
        return 0;
    }
    SDL_FreeSurface(surface);
    surface = NULL;
    return true;
}


void GUI::update(){
    // cout << "Running update()\n";
    drawBoard();
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

    drawAIstatus();

    SDL_RenderPresent(renderer);
    // cout << "Updated()\n";
}
