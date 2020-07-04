#include <SDL2/SDL.h>                                                           
#include <stdio.h>                                                              
#include <iostream>                                                             
#include <vector>                                                             
#include "constants.h"                                                          
#include "GUI.h"                                                                
#include "Mouse.h"
#include "AI.h"
#include "Move.h"

using std::cout, std::endl, std::cerr, std::vector;


int main( int argc, char* args[] )                                              
{                                                                               


    bool gameOver = false;
    Board board = Board();                                                           
    Mouse myMouse = Mouse();

    bool quit = false;

    GUI mygui = GUI(&board);

    vector<AI> aiPlayers;
     aiPlayers.push_back(AI(0, board.getBoard()));
     aiPlayers.push_back(AI(1, board.getBoard()));

    if (mygui.init()){
        SDL_Delay(100);

        SDL_Event e;

        mygui.update();

        unsigned int lastTime = 0; 
        unsigned int currentTime;        

        while(!quit){

            if (SDL_PollEvent (&e) != 0){
                //while (SDL_WaitEvent (&e)) {

                if (e.type == SDL_QUIT){
                    quit = true;
                }

                // else if keyboard actions...

                if (!gameOver)
                {
                    if (myMouse.mouseEvents(e, board)){

                        mygui.update();

                        if (board.testMate()){
                            cout << "************************************\n";
                            cout << "*******************CHECKMATE!!!" << endl;
                            cout << "********************PLAYER WINS*****\n";
                            cout << "************************************\n";
                            mygui.drawTextMate();
                            gameOver = true;
                        }

                        else if (board.testCheck()){
                            cout << "Check!\n";
                            mygui.drawTextCheck();
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

                            for (auto ai : aiPlayers){
                                if ((board.atMove() == ai.getColor()) && (lastTime % 2 == board.atMove())){
                                    Move move = ai.pickMove();
                                    board.movePiece(
                                            move.getOldX(),
                                            move.getOldY(),
                                            move.getNewX(),
                                            move.getNewY()
                                            );
                                    mygui.update();
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
                                    else if (board.testCheck()){
                                        cout << "Check!\n";
                                        mygui.drawTextCheck();
                                    }
                                }
                            }

                            lastTime = currentTime;
                        }
                    }
                }



            }// end while not quit

        } // end if mygui
        return EXIT_SUCCESS;
    }                                                                           


