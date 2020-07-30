#include <SDL2/SDL.h>                                                           
#include <cstdio>
#include <iostream>                                                             
#include <string>
#include "GUI.h"
#include "Mouse.h"
#include "Touch.h"
#include "AI.h"
#include "AIMove.h"

using std::cout, std::endl, std::cerr;

int main( int argc, char* args[] )                                              
{                                                                               
    int whitePly = 2;
    int blackPly = 2;

    if (argc > 1 && argc < 4){
        try {
            whitePly = std::stoi(args[1]);
            cout << "AI for white is set to " << whitePly << ". (default=2)\n";

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
            cout << "AI for black is set to " << blackPly << ". (default=2)\n";
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


    bool gameOver = false;
    Board gameBoard = Board();                                                           
    Mouse myMouse(&gameBoard);
    Touch myTouch(&gameBoard);
    AI ai[] = {AI(false, &gameBoard), AI(true, &gameBoard)} ;
    ai[1].setPly(whitePly);
    ai[0].setPly(blackPly);

    bool quit = false;

    GUI myGUI = GUI(&gameBoard);
    myGUI.setMouse(&myMouse);
    myGUI.setTouch(&myTouch);

    if (myGUI.init()){
        SDL_Delay(100);

        SDL_Event e;

        myGUI.update();

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
                            // myGUI.drawTextMate();
                            gameOver = true;
                        }

                        // else test check... then myGUI.drawTextCheck().
                        // move test section from GUI::drawTextCheck() to Board
                    }


                } // end if !gameOver

            } // end while SDL_PollEvent...


                // AI moves
            else {
                if (!gameOver){
                    currentTime = SDL_GetTicks();
                    if (currentTime > (lastTime + 1000)) {

                        if ((gameBoard.getPlayerAI(gameBoard.atMove()) == 1) && (lastTime % 2 == gameBoard.atMove())){ // remove last condition?
                            AIMove move = ai[gameBoard.atMove()].pickMove();

                            if (move.getOldX() != -1){
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
                                // myGUI.drawTextMate();
                                gameOver = true;
                            }

                            myGUI.update();

                        }

                        lastTime = currentTime;
                    }
                } // end (if not gameOver)
            } // end else

            // update every 50ms except when AI has just made
            // a move. To avoid two AI moves floating together
            if (currentUpdateTime > lastUpdateTime + 50 &&
                (currentTime - lastTime > 600)){
                myGUI.update();
                lastUpdateTime = currentUpdateTime;
            }

            if (currentUpdateTime > lastUpdateTime + 50){
                myGUI.update();
                lastUpdateTime = currentUpdateTime;
                myGUI.update();

            }


        }// end while not quit


    } // end if myGUI
    return EXIT_SUCCESS;
}


