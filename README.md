# Cowchess
A basic chess engine with GUI. This is a computer programming course project 
for summer 2020.

Program written in C++ (GCC C++17 standard) using SDL2. 

Developed on Ubuntu 18.04 and Debian 10. Testing is also done on different
Raspberry Pi's (Raspbian and Raspberry Pi OS). Touch controls works with
Raspberry Pi "Official 7 touch display", other touch screens are untested.

Program should compile on most modern Linux machines with neccessary packages,
including a GCC/C++ compiler with C++17 standard. The source code can easily be
adjusted to pre-C++17 compilers.

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
make, gcc/build-essentials
libsdl2, including libsd2-image-dev
