#include <SDL2/SDL.h>                                                           
#include <stdio.h>                                                              
#include <iostream>                                                             
#include <vector>                                                             
#include <string>
#include "constants.h"                                                          
#include "GUI.h"                                                                
#include "Mouse.h"
#include "Touch.h"
#include "AI.h"
#include "AIMove.h"

using std::cout; 
using std::endl; 
using std::cerr; 
using std::vector;


int main( int argc, char* args[] )                                              
{                                                                               
    int whitePly = 4;
    int blackPly = 4;

    if (argc > 1 && argc < 4){
        try {
            whitePly = std::stoi(args[1]);
            cout << "AI for white is set to " << whitePly << ". (default=4)\n";

        }
        catch (std::invalid_argument const& e){
            cerr << "Error: Invalid argument.\n";
            exit(EXIT_FAILURE);
        }
        catch (std::out_of_range const& e){
            cerr << "Error: Argument out of range\n";
            exit(EXIT_FAILURE);
        }
    }

    if (argc == 3){
        try {
            blackPly = std::stoi(args[2]);
            cout << "AI for black is set to " << blackPly << ". (default=4)\n";
        }
        catch (std::invalid_argument const& e){
            cerr << "Error: Invalid argument.\n";
            exit(EXIT_FAILURE);
        }
        catch (std::out_of_range const& e){
            cerr << "Error: Argument out of range\n";
            exit(EXIT_FAILURE);
        }
    }


    bool aiIsMoving = false;
    bool gameOver = false;
    Board gameBoard = Board();                                                           
    Mouse myMouse = Mouse(&gameBoard);
    Touch myTouch = Touch(&gameBoard);
    AI ai[] = {AI(0, &gameBoard), AI(1, &gameBoard)} ;
    ai[1].setPly(whitePly);
    ai[0].setPly(blackPly);

    bool quit = false;

    GUI mygui = GUI(&gameBoard);
    mygui.setMouse(&myMouse);
    mygui.setTouch(&myTouch);

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
                    // if (!gameBoard.playerCanMove()){
                    //     gameOver = true;
                    // }
                    if ((e.type == SDL_FINGERDOWN || e.type == SDL_FINGERUP || e.type == SDL_FINGERMOTION) && myTouch.touchEvents(e, gameBoard) && gameBoard.getPlayerAI(gameBoard.atMove()) == 0){

                        // cout << "main: " << e.tfinger.x << ":" << e.tfinger.y << endl;
                        // cout << "main: " << e.tfinger.x * SCREEN_WIDTH << ":" << e.tfinger.y * SCREEN_HEIGHT << endl;



                        if (gameBoard.getLastMove().noMoves()){
                            gameOver = true;
                        }
                    }

                    else if (myMouse.mouseEvents(e, gameBoard) && gameBoard.getPlayerAI(gameBoard.atMove()) == 0){
                        lastTime = SDL_GetTicks();


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
                        if (currentTime > (lastTime + 1000) && !aiIsMoving) {

                            if ((gameBoard.getPlayerAI(gameBoard.atMove()) == 1) && (lastTime % 2 == gameBoard.atMove())){ // remove last condition?
                                aiIsMoving = true;
                                AIMove move = ai[gameBoard.atMove()].pickMove();

                                if (!(move.getOldX() == -1)){
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

                            mygui.update();

                            }

                            lastTime = currentTime;
                            aiIsMoving = false;
                        }
                    } // end (if not gameOver)
                } // end else

                // update every 50ms except when AI has just made
                // a move. To avoid two AI moves floating together
                if (currentUpdateTime > lastUpdateTime + 50 && 
                        (currentTime - lastTime > 600)){
                    mygui.update();
                    lastUpdateTime = currentUpdateTime;
                }

                if (currentUpdateTime > lastUpdateTime + 50){
                    mygui.update();
                    lastUpdateTime = currentUpdateTime;
                    mygui.update();

                }


            }// end while not quit


        } // end if mygui
        return EXIT_SUCCESS;
    }                                                                           


