#OBJS specifies which files to compile as part of the project
OBJS = main.cpp GUI.cpp Board.cpp Piece.cpp Mouse.cpp Rook.cpp King.cpp AI.cpp Move.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = cowchess

#Compiler
CXX = g++

#Flags
CXXFLAGS = -Wall -std=c++1z -lSDL2 -lSDL2_image

# ############# compile the executable
cowchess: main.o GUI.o Board.o Piece.o Mouse.o Rook.o King.o AI.o Move.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_NAME) main.o GUI.o Board.o Piece.o Mouse.o Rook.o King.o AI.o Move.o


# ########## compile objects
main.o: main.cpp constants.h GUI.h Mouse.h AI.h Move.h
	$(CXX) $(CXXFLAGS) -c main.cpp

GUI.o: GUI.h constants.h Piece.h

Board.o: Board.h Piece.h Rook.h King.h constants.h

Piece.o: Piece.h Board.h img/piece.xpm img/piece_w.xpm img/piece_b.xpm

Mouse.o: Mouse.h Board.h constants.h Piece.h

Rook.o: Rook.h Board.h Piece.h img/rook_w.xpm img/rook_b.xpm

King.o: King.h Board.h Piece.h img/king_w.xpm img/king_b.xpm

AI.o: AI.h Move.h Piece.h

Move.o: Move.h Piece.h

#This is the target that compiles our executable
all : $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(OBJ_NAME)
