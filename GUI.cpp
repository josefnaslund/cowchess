#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstring>
#include <iostream>
#include "GUI.h"
#include "constants.h"
#include "Piece.h"

using std::cout, std::endl;

GUI::GUI(Board* _gameBoard)
{
    window = NULL;
    renderer = NULL;
    texture = NULL;
    images = std::vector<std::pair<const char**, SDL_Texture*>> {};
    surface = NULL;
    gameBoard = _gameBoard;

}

GUI::~GUI(){
        for (auto p : images){
                SDL_DestroyTexture(p.second);
        }

        images.clear();
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
    // SDL_RenderPresent(renderer);
    // SDL_Delay(100);

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

            // send to screen
            //SDL_RenderPresent(renderer);
            // SDL_Delay(1);
        }
    }

    drawText();
    drawInfo();
}

void GUI::drawText(){
    TTF_Font* myFont = TTF_OpenFont("img/FreeMonoBold.ttf", 600);
    SDL_Color Black = {0, 0, 0};
    SDL_Surface* surf = TTF_RenderText_Solid(myFont, "Turn", Black);
    SDL_Texture* Text = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_Rect r; 
    r.x = 21;  
    r.y = 40; 
    r.w = 75; 
    r.h = 45; 

    SDL_RenderCopy(renderer, Text, NULL, &r);

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(Text);
}




void GUI::drawTextCheck(){
    Piece*** board = gameBoard->getBoard();

    TTF_Font* myFont = TTF_OpenFont("img/FreeMonoBold.ttf", 600);
    SDL_Color Black = {0, 0, 0};
    SDL_Surface* surf = TTF_RenderText_Solid(myFont, "Check", Black);
    SDL_Texture* Text = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_Rect r; 
    r.x = 15;  
    r.y = 180; 
    r.w = 85; 
    r.h = 45; 

    SDL_RenderCopy(renderer, Text, NULL, &r);

    // delay cause of just drawn board (for slower machines)
    SDL_Delay(300); 
    SDL_RenderPresent(renderer);
    
    // delay before destruction
    SDL_Delay(300); 

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(Text);

}

void GUI::drawTextMate(){
    TTF_Font* myFont = TTF_OpenFont("img/FreeMonoBold.ttf", 600);
    SDL_Color Col = {200, 50, 50};
    SDL_Surface* surf = TTF_RenderText_Solid(myFont, "Checkmate!", Col);
    SDL_Texture* Text = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_Rect r; 
    r.x = LEFT_MARGIN + 8 * SQUARE_SIZE / 2 - 190 / 2;   // == 225
    r.y = TOP_MARGIN + 8 * SQUARE_SIZE / 2 - 45/2;  // == 217
    r.w = 190; 
    r.h = 45; 

    SDL_RenderCopy(renderer, Text, NULL, &r);

    // delay cause of just drawn board (for slower machines)
    SDL_Delay(300); 
    SDL_RenderPresent(renderer);
    // delay before destruction
    SDL_Delay(300); 

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(Text);

}


void GUI::drawInfo(){


    SDL_Rect r;

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



void GUI::loadImages(){
    Piece*** board = gameBoard->getBoard();
    // SDL_Rect r;

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
        std::cout << "vector 'images' is empty\n";
        loadImages();
        std::cout << "There are now " << images.size() << " images in vector\n";
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
                // SDL_RenderPresent(renderer);
                // SDL_Delay(1);
                //
                // if (texture){
                //         SDL_DestroyTexture(texture);
                // }
                // SDL_Delay(100);
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

    return 1;
}


void GUI::update(){
    cout << "Running update()\n";
    drawBoard();
    drawPieces();
    SDL_RenderPresent(renderer);
    cout << "Updated()\n";
}
