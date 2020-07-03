#OBJS specifies which files to compile as part of the project
OBJS = main.cpp GUI.cpp Board.cpp Piece.cpp Mouse.cpp Rook.cpp King.cpp AI.cpp Move.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = program

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -Wall -std=c++1z -lSDL2 -lSDL2_image -lSDL2_ttf -o $(OBJ_NAME)
