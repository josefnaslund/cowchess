#ifndef GUI_H
#define GUI_H

#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include <utility> // std::pair
#include "Mouse.h"
#include "Touch.h"

class Board; // Forward declaration

/**
 * @brief For representing chessgame in SDL2.
 */
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
        SDL_Texture** promotionTextureWhite;
        SDL_Texture** promotionTextureBlack;
        SDL_Texture* wood;
        Mouse* mouse;
        Touch* touch;


    public:
        /**
         * @brief Constructor, GUI needs pointer to a Board. Board keeps track of game and pieces on the board.
         *
         * @param _gameBoard Pointer to current game Board.
         */
        explicit GUI(Board* _gameBoard);

        /**
         * @brief Destructor clears up texture allocated memory on close
         */
        ~GUI();


        /**
         * @brief Initialize GUI Window
         *
         * @return True if success
         */
        bool init();

        /**
         * @brief Set a pointer to mouse object
         *
         * @param _mouse
         */
        void setMouse(Mouse* _mouse);

        /**
         * @brief Set a pointer to touch object
         *
         * @param _touch
         */
        void setTouch(Touch* _touch);


        /**
         * @brief Draws background and game board squares to renderer.
         * Background behind board is set to a strip of wood (image).
         * Calls member drawTurn().
         */
        void drawBoard();

        /**
         * @brief Draws text info image and calls SDL_RenderPresent().
         * Also some SDL_Delay().
         */
        void drawTextCheck();


        /**
         * @brief Draws a checkmate message. Does not present, only sends to renderer.
         */
        void drawTextMate();


        /**
         * $brief Draws a 'Draw' message. Does not present, only sends to renderer.
         */
        void drawTextDraw();

        /**
         * @brief Draws text image and squares representing who's turn
         * it is (color square).
         */
        void drawTurn();


        /**
         * @brief Draws squares with status of AI activation.
         */
        void drawAIstatus();

        /**
         * @brief Drawing captured pieces on right side of the board, grouping
         * by color.
         */
        void drawCapturedPieces();

        /**
         * @brief Draws pieces to choose from on promotion
         */
        void drawPromotionPieces(bool color);

        /**
         * @brief Loads textures of board's pieces to vector-pair "images".
         */
        void loadImages();

        /**
         * @brief Searches for a image in vector 'images'
         *
         * @param img pointer to image array, identifier
         *
         * @return index in vector 'images' of the texture for that piece
         */
        int findImage(const char** img);

        /**
         * @brief Draws pieces on the current board to rendererer.
         */
        void drawPieces();

        /**
         * @brief Draw a gripped piece to mouse positions, and replaces pieces
         * home square.
         */
        void drawCurrentPieceMouse();

        /**
         * @brief Draw a gripped piece to touch positions, and replaces pieces
         * home square.
         */
        void drawCurrentPieceTouch();

        bool close(); //????


        /**
         * @brief Draws a straight line highlighting the last move
         */
        void drawLastMove();

        /**
         * @brief Calls members drawBoard(), drawPieces() and
         * SDL_RenderPresent().
         * Should be called on every update of the board.
         */
        void update();

        /**
         * @brief Makes SDL textures out of images stored in xpm format
         *
         * @param img Pointer to image array
         *
         * @return True on success.
         */
        bool loadTexture(const char** img);
};

#endif
