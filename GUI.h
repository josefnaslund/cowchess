#ifndef GUI_H
#define GUI_H

#include <string>
#include <SDL2/SDL.h>
#include "Board.h"
#include "Piece.h"

class GUI {
        private:
            SDL_Window* window;
            SDL_Renderer* renderer;
            SDL_Texture* texture;
            bool updated;

        public:
            GUI();
            bool init();
            void drawBoard();
            void drawPieces(Piece** board);
            bool update();
            bool close();
            bool isUpdated();
            bool loadImage(std::string img);
};

#endif
