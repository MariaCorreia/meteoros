#OBJS specifies which files to compile as part of the project
# OBJS = exemplo.cpp
OBJ = main.cpp Objects/Entity.cpp Objects/House.cpp 
#EXT = .cpp
#code.c

#CC specifies which compiler we're using
CC = g++
# CC = clang

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall -Wpedantic -g

#LINKER_FLAGS specifies the libraries we're linking against
#-lXmu -lXext -lXi -lX11 -lm
#-lm -lpthread -lSDL2
LINKER_FLAGS = -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio 

all: objects
# routine to run
objects: 
	$(CC) $(OBJ) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o main
#	$(CC) $(OBJ)$(EXT) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ)

# example code to clean stuff
#clean:
#	rm $(OBJ)