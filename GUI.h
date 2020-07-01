#ifndef GUI_H
#define GUI_H

#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include "Piece.h"

class GUI {
        private:
            SDL_Window* window;
            SDL_Renderer* renderer;
            SDL_Texture* texture;
            std::vector<std::pair<const char**, SDL_Texture*>> images;
            SDL_Surface* surface;
            Board* gameBoard;

        public:
            GUI(Board* _gameBoard);
            ~GUI(); // SDL_DestroyTexture on all textures in vector
            bool init();
            void drawBoard();
            void drawInfo();
            void loadImages();
            int findImage(const char** img);
            void drawPieces();
            bool close();
            void update();
            bool loadTexture(const char** img);
};

#endif
