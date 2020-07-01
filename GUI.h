#ifndef GUI_H
#define GUI_H

#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include "Board.h"
#include "Piece.h"

class GUI {
        private:
            SDL_Window* window;
            SDL_Renderer* renderer;
            SDL_Texture* texture;
            std::vector<std::pair<const char**, SDL_Texture*>> images;
            SDL_Surface* surface;

        public:
            GUI();
            ~GUI(); // SDL_DestroyTexture on all textures in vector
            bool init();
            void drawBoard();
            void loadImages(Piece*** board);
            int findImage(const char** img);
            void drawPieces(Piece*** board);
            bool close();
            void update(Piece*** board);
            bool loadTexture(const char** img);
};

#endif
