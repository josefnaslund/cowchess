# Directory for object files
DIRO := objects

#OBJS specifies which files to compile as part of the project
TEMPOBJS = main.o GUI.o Board.o Piece.o Mouse.o Rook.o King.o AI.o Move.o

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
CXXFLAGS := -Wall -std=c++1z
OBJFLAGS := -I$(DIRH) -I$(DIRIMG)
LIBFLAGS := -lSDL2 -lSDL2_image

# ############# compile the executable
$(OBJ_NAME) : $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBFLAGS)


# ########## compile objects
#

# COMMENTED OUT: does not regognize updates in header files
# $(DIRO)/%.o: $(DIRCXX)%.cpp
# 	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<


$(DIRO)/main.o : $(DIRCXX)/main.cpp $(DIRH)/constants.h $(DIRH)/GUI.h $(DIRH)/Mouse.h $(DIRH)/AI.h $(DIRH)/Move.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/GUI.o : $(DIRCXX)/GUI.cpp $(DIRH)/GUI.h $(DIRH)/constants.h $(DIRH)/Piece.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Board.o : $(DIRCXX)/Board.cpp $(DIRH)/Board.h $(DIRH)/Piece.h $(DIRH)/Rook.h $(DIRH)/King.h $(DIRH)/constants.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Piece.o : $(DIRCXX)/Piece.cpp $(DIRH)/Piece.h $(DIRH)/Board.h $(DIRIMG)/piece.xpm $(DIRIMG)/piece_w.xpm $(DIRIMG)/piece_b.xpm
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Mouse.o : $(DIRCXX)/Mouse.cpp $(DIRH)/Mouse.h $(DIRH)/Board.h $(DIRH)/constants.h $(DIRH)/Piece.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Rook.o : $(DIRCXX)/Rook.cpp $(DIRH)/Rook.h $(DIRH)/Board.h $(DIRH)/Piece.h $(DIRIMG)/rook_w.xpm $(DIRIMG)/rook_b.xpm
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/King.o : $(DIRCXX)/King.cpp $(DIRH)/King.h $(DIRH)/Board.h $(DIRH)/Piece.h $(DIRIMG)/king_w.xpm $(DIRIMG)/king_b.xpm
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/AI.o : $(DIRCXX)/AI.cpp $(DIRH)/AI.h $(DIRH)/Move.h $(DIRH)/Piece.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

$(DIRO)/Move.o : $(DIRCXX)/Move.cpp $(DIRH)/Move.h $(DIRH)/Piece.h
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<

# $(DIRO)/%.o : $(DIRIMG)/%.xpm
# 	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<
