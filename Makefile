#OBJS specifies which files to compile as part of the project
OBJS = main.cpp GUI.cpp Board.cpp Piece.cpp Mouse.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = program

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -w -lSDL2 -lSDL2_image -o $(OBJ_NAME)
