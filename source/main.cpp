#include <SDL2/SDL.h>                                                           
#include <stdio.h>                                                              
#include <iostream>                                                             
#include <vector>                                                             
#include "constants.h"                                                          
#include "GUI.h"                                                                
#include "Mouse.h"
#include "AI.h"
#include "Move.h"

using std::cout; 
using std::endl; 
using std::cerr; 
using std::vector;


int main( int argc, char* args[] )                                              
{                                                                               


    bool gameOver = false;
    Board board = Board();                                                           
    Mouse myMouse = Mouse(&board);
    AI ai[] = {AI(0, &board), AI(1, &board)} ;

    bool quit = false;

    GUI mygui = GUI(&board);

    if (mygui.init()){
        SDL_Delay(100);

        SDL_Event e;

        mygui.update();

        // AI Delay
        unsigned int lastTime = 0; 
        unsigned int currentTime;        

        // update time
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
                    if (!board.playerCanMove()){
                            gameOver = true;
                            cout << "\n**** It's a draw ****" << endl;
                    }
                    if (myMouse.mouseEvents(e, board) && board.getPlayerAI(board.atMove()) == 0){

                        // mygui.update();

                        if (board.testMate()){
                            cout << "\n************************************\n";
                            cout << "*******************CHECKMATE!!!" << endl;
                            cout << "********************PLAYER WINS*****\n";
                            cout << "************************************\n";
                            mygui.drawTextMate();
                            gameOver = true;
                        }


                        // else test check... then mygui.drawTextCheck().
                        // move test section from GUI::drawTextCheck() to Board

                    }





                } // end if !gameOver

            } // end while SDL_PollEvent...


                else {
                    if (!gameOver){
                        currentTime = SDL_GetTicks();
                        if (currentTime > lastTime + 1000) {

                                if ((board.getPlayerAI(board.atMove()) == 1) && (lastTime % 2 == board.atMove())){
                                    Move move = ai[board.atMove()].pickMove();
                                    if (!move.isInvalid()){
                                    board.movePiece(
                                            move.getOldX(),
                                            move.getOldY(),
                                            move.getNewX(),
                                            move.getNewY()
                                            );
                                    // mygui.update();
                                    }

                                    else {
                                            gameOver = true;
                                            cout << "\n**************\n";
                                            cout << "AI cannot move\n";
                                            cout << "It's a draw\n";
                                            cout << "***********" << endl;
                                    }
                                    // if (aiPlayers.size() == 2)
                                    //     SDL_Delay(500);

                                    if (board.testMate()){
                                        cout << "************************************\n";
                                        cout << "*******************CHECKMATE!!!" << endl;
                                        cout << "********************AI WINS!!*******\n";
                                        cout << "************************************\n";
                                        mygui.drawTextMate();
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


