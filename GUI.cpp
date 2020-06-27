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
    updated = 1;
    images = std::vector<std::pair<std::string, SDL_Texture*>> {};

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
    SDL_RenderPresent(renderer);
    SDL_Delay(150);

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
            SDL_RenderPresent(renderer);
            SDL_Delay(5);
        }
    }
}

void GUI::loadImages(Piece*** board){
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
                    loadImage(board[row][col]->getImage());
                    if (texture){
                            std::pair<std::string, SDL_Texture*> newPair 
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

int GUI::findImage(std::string str){
    for (uint i = 0; i != images.size(); ++i){
            if (images[i].first == str){
                    return i;
            }
    }
    return -1;
}

void GUI::drawPieces(Piece*** board){
    if (images.empty()){
        loadImages(board);
    }

    // to draw pieces
    SDL_Rect r;

    for (int row = 0; row != 8; ++row){
        for (int col = 0; col != 8; ++col){
            if (board[row][col]->isAlive()){
                r.x = 120 + col * 50;
                r.y = 40 + (7 - row) * 50;
                r.w = 50;
                r.h = 50;
                int index = findImage(board[row][col]->getImage());
                if (index != -1 && images[index].second) {
                    SDL_RenderCopy(renderer, images[index].second, nullptr, &r);
                }

                else {
                    SDL_RenderFillRect( renderer, &r );
                }
                SDL_RenderPresent(renderer);
                if (texture){
                        SDL_DestroyTexture(texture);
                }
                // SDL_Delay(100);
            }
        }
    }
}

bool GUI::loadImage(std::string img){
    texture = NULL;
    texture = IMG_LoadTexture(renderer, img.c_str());
    if (!texture){
        std::cerr << "Can't load texture: " << img << std::endl;
        return 0;
    }
    // SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    return 1;
}


void GUI::setUpdated(bool b){
        if (b)
            ++updated;
        else
            --updated;
}

bool GUI::isUpdated(){
    return updated;
}
