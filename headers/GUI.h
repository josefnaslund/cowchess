#ifndef GUI_H
#define GUI_H

#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include <utility>

class Board;

class GUI {
        private:
            SDL_Window* window;
            SDL_Renderer* renderer;
            SDL_Texture* texture;
            std::vector<std::pair<const char**, SDL_Texture*>> images;
            SDL_Surface* surface;
            Board* gameBoard;
            SDL_Texture* turnTexture;
            SDL_Texture* checkTexture;


        public:
            GUI(Board* _gameBoard);
            ~GUI(); // SDL_DestroyTexture on all textures in vector
            bool init();
            void drawBoard();

            void drawTextCheck();
            void drawTextMate();

            void drawTurn();
            void loadImages();
            int findImage(const char** img);
            void drawPieces();
            bool close();
            void update();
            bool loadTexture(const char** img);
};

#endif
