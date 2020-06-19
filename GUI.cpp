#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cstring>
#include <iostream>
#include "GUI.h"
#include "constants.h"
#include "Board.h"
#include "Piece.h"

using std::cout, std::endl;

GUI::GUI()
{
    window = NULL;
    renderer = NULL;
    texture = NULL;
    updated = true;

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

            if ((row + col) % 2){
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
            SDL_RenderPresent(renderer);
        }
    }
}

void GUI::drawPieces(Piece** board){
    // to draw pieces
    SDL_Rect r;

    // cout << "4.1\n";
    for (int row = 0; row != 8; ++row){
        // cout << "4.2\n";
        for (int col = 0; col != 8; ++col){
            // cout << "4.3\n";
            if (board[row][col].isExist()){
                // cout << "4.4\n";
                r.x = 120 + col * 50;
                r.y = 40 + (7 - row) * 50;
                r.w = 50;
                r.h = 50;
                cout << "4.40 About to load image from [" << 7-row << "][" << col << "]\n";
                cout << "Image: " << board[row][col].getImage() << endl;
                // cout << "4.41 about to load image\n";
                loadImage(board[row][col].getImage());
                if (texture) {
                    SDL_RenderCopy(renderer, texture, nullptr, &r);
                }
                // cout << "4.5\n";

                else {
                    SDL_RenderFillRect( renderer, &r );
                }
                SDL_RenderPresent(renderer);
                if (texture){
                        SDL_DestroyTexture(texture);
                }
                SDL_Delay(1000);
                // cout << "4.6\n";
            }
        }
    }
}

bool GUI::loadImage(std::string img){
    // cout << "4.415 Hello from loadImage\n";
    int w = 0, h = 0;

    //cout << "4.42 to load texture\n";
    texture = NULL;
    texture = IMG_LoadTexture(renderer, img.c_str());
    if (!texture){
        std::cerr << "Can't load texture: " << img << std::endl;
    }
    // SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    return 1;
}


bool GUI::isUpdated(){
    if (updated){
        updated = false;
        return true;
    }
    return false;
}
