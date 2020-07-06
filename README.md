# Cowchess
Early development of a basic chess engine with GUI. This is a project for
summer 2020.

Program written in C++ (GCC C++17 standard) using SDL2. 

Developed on Ubuntu 18.04 and Debian 10. Tested is also done on different
Raspberry Pi's (Raspbian and Raspberry Pi OS).

## Current state
* Checking and mate is possible.
* Only King and Rook pieces. No castling yet. Will work on Pawn this week.
* AI players are set in main.cpp file at this moment. AI is very basic, piece
hungry.

## Some known dependencies
make, gcc/build-essentials
libsdl2, including libsd2-image-dev
