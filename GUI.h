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
            std::vector<std::pair<std::string, SDL_Texture*>> images;
            
            int updated;

        public:
            GUI();
            ~GUI(); // SDL_DestroyTexture on all textures in vector
            bool init();
            void drawBoard();
            void loadImages(Piece*** board);
            int findImage(std::string str);
            void drawPieces(Piece*** board);
            void setUpdated(bool b);
            bool close();
            bool isUpdated();
            void update(Piece*** board);
            bool loadImage(std::string img);
};

#endif
