A basic chess engine with GUI and AI. This is a computer programming course project 
for summer 2020.

Program written in C++ (GCC C++17 standard) using SDL2. 

Developed on Ubuntu 18.04 and Debian 10. Testing is also done on different
Raspberry Pi's (Raspbian and Raspberry Pi OS). Touch controls works with
Raspberry Pi "Official 7 touch display", other touch screens are untested.

Program should compile on most modern Linux machines with neccessary packages,
including a GCC/C++ compiler with C++17 standard. The source code can easily be
adjusted to pre-C++17 compilers.

## Install notes for Debian based distros.
* Note: Compiler should have support for C++17, so a newer and updated distro is required.
* $ sudo apt install git make build-essential libsdl2-image-dev
* $ git clone https://github.com/josefnaslund/cowchess
* $ cd cowchess
* $ make
* $ sudo make install

## Playing the game
* Start the game with *cowchess* command.
* Arguments. First argument is white AI level, second for black. 
Choose AI level in range 0-3, level 4 normally takes minutes for each move. Default AI is 2.
* To turn on/off AI click on the boxes in lower left corner of window. Left for white, right is black.
* Pieces are moved with drag and drop, either pointing device or touch screen.
* The standard output recives long algebraic chess notation during the game.
* Store the notation with *$ cowchess | tee player_vs_ai.txt*
* You can not undo moves. Be careful.
* You can not restart ongoing or finished game without restarting program. It's a feature not a bug, so each game can be
  stored to own text file with command above.


## Current state
* Working chess game with all pieces. It seem to conform with standard rules.
* AI is fine for weak players like author. Sometimes I win on default AI
settings (level 2), sometimes I loose.
* Setting AI level to 4 will take to long on most machines (minutes per move,
depending on how many moves are possible). Higher than 4 is not advised.

## License
Program code is licensed under GNU GPL v3. You are free do distribute, make any
changes you would like to source code and redistribute with reference to
original.

## Some known dependencies
make, gcc/build-essentials, SDL2 (libsdl2 including libsd2-image-dev)
