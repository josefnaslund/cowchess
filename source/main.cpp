#include <SDL2/SDL.h>                                                           
#include <stdio.h>                                                              
#include <iostream>                                                             
#include <vector>                                                             
#include "constants.h"                                                          
#include "GUI.h"                                                                
#include "Mouse.h"
#include "Touch.h"
#include "AI.h"
#include "Move.h"

using std::cout; 
using std::endl; 
using std::cerr; 
using std::vector;


int main( int argc, char* args[] )                                              
{                                                                               


    bool gameOver = false;
    Board gameBoard = Board();                                                           
    Mouse myMouse = Mouse(&gameBoard);
    Touch myTouch = Touch(&gameBoard);
    AI ai[] = {AI(0, &gameBoard), AI(1, &gameBoard)} ;

    bool quit = false;

    GUI mygui = GUI(&gameBoard);

    if (mygui.init()){
        SDL_Delay(100);

        SDL_Event e;

        mygui.update();

        // AI Delay
        unsigned int lastTime = 0; 
        unsigned int currentTime;        

        // GUI update timer
        unsigned int lastUpdateTime = 0;
        unsigned int currentUpdateTime;

        while(!quit){

            currentUpdateTime = SDL_GetTicks();
            if (SDL_PollEvent (&e) != 0){
                //while (SDL_WaitEvent (&e)) {

                if (e.type == SDL_QUIT){
                    quit = true;
                }




                // else if keyboard actions...

                if (!gameOver)
                {
                    if (!gameBoard.playerCanMove()){
                        gameOver = true;
                    }
                    else if ((e.type == SDL_FINGERDOWN || e.type == SDL_FINGERUP) && myTouch.touchEvents(e, gameBoard) && gameBoard.getPlayerAI(gameBoard.atMove()) == 0){

                        // cout << "main: " << e.tfinger.x << ":" << e.tfinger.y << endl;
                        // cout << "main: " << e.tfinger.x * SCREEN_WIDTH << ":" << e.tfinger.y * SCREEN_HEIGHT << endl;



                        if (gameBoard.getLastMove().noMoves()){
                            gameOver = true;
                        }
                    }

                    else if (myMouse.mouseEvents(e, gameBoard) && gameBoard.getPlayerAI(gameBoard.atMove()) == 0){


                        if (gameBoard.getLastMove().noMoves()){
                            // mygui.drawTextMate();
                            gameOver = true;
                        }

                        // else test check... then mygui.drawTextCheck().
                        // move test section from GUI::drawTextCheck() to Board
                    }


                } // end if !gameOver

            } // end while SDL_PollEvent...


            // AI moves
                else {
                    if (!gameOver){
                        currentTime = SDL_GetTicks();
                        if (currentTime > lastTime + 1000) {

                            if ((gameBoard.getPlayerAI(gameBoard.atMove()) == 1) && (lastTime % 2 == gameBoard.atMove())){ // remove last condition?
                                Move move = ai[gameBoard.atMove()].pickMove();
                                if (!move.isInvalid()){
                                    gameBoard.movePiece(
                                            move.getOldX(),
                                            move.getOldY(),
                                            move.getNewX(),
                                            move.getNewY()
                                            );
                                }

                                else {
                                    gameOver = true;
                                }

                                if (gameBoard.getLastMove().isCheck() && gameBoard.getLastMove().noMoves()){
                                    // mygui.drawTextMate();
                                    gameOver = true;
                                }
                            }

                            lastTime = currentTime;
                        }
                    }
                }

                if (currentUpdateTime > lastUpdateTime + 50){
                    mygui.update();
                    lastUpdateTime = currentUpdateTime;
                }


            }// end while not quit

        } // end if mygui
        cout << endl;
        return EXIT_SUCCESS;
    }                                                                           


