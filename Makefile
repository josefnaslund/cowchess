# Directory for object files
DIRO := objects

#OBJS specifies which files to compile as part of the project
TEMPOBJS = main.o GUI.o Board.o Piece.o Mouse.o Rook.o King.o AI.o Move.o

# Replace path on objects
OBJS = $(patsubst %.o,$(DIRO)/%.o,$(TEMPOBJS))

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = cowchess

#Compiler
CXX = g++

# Directory for .h files
DIRH := headers/

# Directory for .cpp files
DIRCXX := source/

# Directory for .xpm files
DIRIMG := img/

# Create directory if not exists
_dircreate := $(shell mkdir -p $(DIRO))


#Flags
CXXFLAGS := -Wall -std=c++1z
OBJFLAGS := -I$(DIRH) -I$(DIRIMG)
LIBFLAGS := -lSDL2 -lSDL2_image

# ############# compile the executable
$(OBJ_NAME): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBFLAGS)


# ########## compile objects
#

$(DIRO)/%.o: $(DIRCXX)%.cpp
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) -c -o $@ $<
