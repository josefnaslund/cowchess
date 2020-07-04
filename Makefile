#OBJS specifies which files to compile as part of the project
OBJS = main.cpp GUI.cpp Board.cpp Piece.cpp Mouse.cpp Rook.cpp King.cpp AI.cpp Move.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = cowchess

#Compiler
CXX = g++

#Flags
CXXFLAGS := -Wall -std=c++1z
LIBFLAGS := -lSDL2 -lSDL2_image

# ############# compile the executable
cowchess: main.o GUI.o Board.o Piece.o Mouse.o Rook.o King.o AI.o Move.o
	$(CXX) -o $(OBJ_NAME) main.o GUI.o Board.o Piece.o Mouse.o Rook.o King.o AI.o Move.o $(CXXFLAGS) $(LIBFLAGS)


# ########## compile objects
main.o: main.cpp constants.h GUI.h Mouse.h AI.h Move.h
	$(CXX) $(CXXFLAGS) -c main.cpp

GUI.o: GUI.h constants.h Piece.h
	$(CXX) $(CXXFLAGS) -c GUI.cpp

Board.o: Board.h Piece.h Rook.h King.h constants.h
	$(CXX) $(CXXFLAGS) -c Board.cpp

Piece.o: Piece.h Board.h img/piece.xpm img/piece_w.xpm img/piece_b.xpm
	$(CXX) $(CXXFLAGS) -c Piece.cpp

Mouse.o: Mouse.h Board.h constants.h Piece.h
	$(CXX) $(CXXFLAGS) -c Mouse.cpp

Rook.o: Rook.h Board.h Piece.h img/rook_w.xpm img/rook_b.xpm
	$(CXX) $(CXXFLAGS) -c Rook.cpp

King.o: King.h Board.h Piece.h img/king_w.xpm img/king_b.xpm
	$(CXX) $(CXXFLAGS) -c King.cpp

AI.o: AI.h Move.h Piece.h
	$(CXX) $(CXXFLAGS) -c AI.cpp

Move.o: Move.h Piece.h
	$(CXX) $(CXXFLAGS) -c Move.cpp

#This is the target that compiles our executable
# all : $(OBJS)
# 	$(CXX) $(OBJS) $(CXXFLAGS) -o $(OBJ_NAME)
