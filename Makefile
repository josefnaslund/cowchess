.PHONY: all
.PHONY: clean
.PHONY: install
.PHONY: uninstall

# Directory for object files
DIRO := objects

#OBJS specifies which files to compile as part of the project
TEMPOBJS = main.o GUI.o Board.o Piece.o Mouse.o Touch.o Rook.o King.o Queen.o Pawn.o Knight.o Bishop.o AI.o AIMove.o LastMove.o Player.o

# Replace path on objects
OBJS = $(patsubst %.o,$(DIRO)/%.o,$(TEMPOBJS))

# $(DIRO)/king_b.o $(DIRO)/king_w.o $(DIRO)/piece.o $(DIRO)/piece_w.o $(DIRO)/piece_b.o $(DIRO)/rook_w.o $(DIRO)/rook_b.o

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = cowchess

#Compiler
CXX = g++

# Directory for .h files
DIRH := headers

# Directory for .cpp files
DIRCXX := source

# Directory for .xpm files
DIRIMG := img

# Create directory if not exists
_dircreate := $(shell mkdir -p $(DIRO))

#Flags 
# comment: -Wno-psabi for error messages on Raspberry Pi
CXXFLAGS := -Wall -std=c++17 -Wno-psabi -O2
OBJFLAGS := -I$(DIRH) -I$(DIRIMG)
LIBFLAGS := -lSDL2 -lSDL2_image

all: $(OBJ_NAME)

# ############# compile the executable
$(OBJ_NAME) : $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBFLAGS)


# ########## compile objects
#

# COMMENTED OUT: does not regognize updates in header files
# $(DIRO)/%.o: $(DIRCXX)%.cpp
# 	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<


$(DIRO)/main.o : $(DIRCXX)/main.cpp $(DIRH)/constants.h $(DIRH)/GUI.h $(DIRH)/Mouse.h $(DIRH)/Touch.h $(DIRH)/AI.h $(DIRH)/AIMove.h $(DIRH)/Board.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/GUI.o : $(DIRCXX)/GUI.cpp $(DIRH)/GUI.h $(DIRH)/Mouse.h $(DIRH)/Touch.h $(DIRH)/constants.h $(DIRH)/Piece.h $(DIRIMG)/text_turn.xpm $(DIRIMG)/text_checkmate.xpm $(DIRIMG)/text_check.xpm $(DIRIMG)/text_draw.xpm $(DIRIMG)/queen_w.xpm $(DIRIMG)/queen_b.xpm $(DIRIMG)/rook_w.xpm $(DIRIMG)/rook_b.xpm $(DIRIMG)/knight_b.xpm $(DIRIMG)/knight_w.xpm $(DIRIMG)/bishop_w.xpm $(DIRIMG)/bishop_b.xpm
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Board.o : $(DIRCXX)/Board.cpp $(DIRH)/Board.h $(DIRH)/Piece.h $(DIRH)/Rook.h $(DIRH)/Bishop.h $(DIRH)/King.h $(DIRH)/Pawn.h $(DIRH)/Knight.h $(DIRH)/constants.h $(DIRH)/LastMove.h $(DIRH)/Player.h $(DIRH)/Queen.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Piece.o : $(DIRCXX)/Piece.cpp $(DIRH)/Piece.h $(DIRH)/Board.h $(DIRIMG)/piece.xpm $(DIRIMG)/piece_w.xpm $(DIRIMG)/piece_b.xpm
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Mouse.o : $(DIRCXX)/Mouse.cpp $(DIRH)/Mouse.h $(DIRH)/Board.h $(DIRH)/constants.h $(DIRH)/Piece.h $(DIRH)/Player.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Touch.o : $(DIRCXX)/Touch.cpp $(DIRH)/Touch.h $(DIRH)/Board.h $(DIRH)/constants.h $(DIRH)/Piece.h $(DIRH)/Player.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Rook.o : $(DIRCXX)/Rook.cpp $(DIRH)/Rook.h $(DIRH)/Board.h $(DIRH)/Piece.h $(DIRIMG)/rook_w.xpm $(DIRIMG)/rook_b.xpm
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Bishop.o : $(DIRCXX)/Bishop.cpp $(DIRH)/Bishop.h $(DIRH)/Board.h $(DIRH)/Piece.h $(DIRIMG)/bishop_w.xpm $(DIRIMG)/bishop_b.xpm
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/King.o : $(DIRCXX)/King.cpp $(DIRH)/King.h $(DIRH)/Board.h $(DIRH)/Piece.h $(DIRIMG)/king_w.xpm $(DIRIMG)/king_b.xpm
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Queen.o : $(DIRCXX)/Queen.cpp $(DIRH)/Queen.h $(DIRH)/Rook.h $(DIRH)/Bishop.h $(DIRH)/Board.h $(DIRH)/Piece.h $(DIRIMG)/queen_w.xpm $(DIRIMG)/queen_b.xpm
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Pawn.o : $(DIRCXX)/Pawn.cpp $(DIRH)/Pawn.h $(DIRH)/Board.h $(DIRH)/Piece.h $(DIRIMG)/pawn_w.xpm $(DIRIMG)/pawn_b.xpm $(DIRH)/LastMove.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Knight.o : $(DIRCXX)/Knight.cpp $(DIRH)/Knight.h $(DIRH)/Board.h $(DIRH)/Piece.h $(DIRIMG)/knight_w.xpm $(DIRIMG)/knight_b.xpm
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/AI.o : $(DIRCXX)/AI.cpp $(DIRH)/AI.h $(DIRH)/AIMove.h $(DIRH)/Piece.h $(DIRH)/Board.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/AIMove.o : $(DIRCXX)/AIMove.cpp $(DIRH)/AIMove.h $(DIRH)/Piece.h $(DIRH)/Board.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/LastMove.o : $(DIRCXX)/LastMove.cpp $(DIRH)/LastMove.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Player.o : $(DIRCXX)/Player.cpp $(DIRH)/Player.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

# $(DIRO)/%.o : $(DIRIMG)/%.xpm
# 	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<


install:
	mv cowchess /usr/bin/$(OBJ_NAME)

uninstall:
	rm -f /usr/bin/$(OBJ_NAME)

clean:
	rm -f $(DIRO)/*.o
