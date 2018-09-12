#Cflags used in the compiler
CFLAGS=-Wall -Wpedantic -g
#all libraries used in the project
LINKER_FLAGS = -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
#compiler we're using
CC=g++
#name of the executable created at the end
EXEC=main 
#select all objects with sufix .cpp inside Objects/
SRC= $(wildcard Objects/*.cpp)
#for each .cpp string in SRC, replace .cpp with .o
OBJ=$(SRC:.cpp=.o)

#default command to be executed when no parameter is given to make
all: $(EXEC)
#linker step, verifies dependencies and if any are changed, recompiles it. Lastly, links everything up and creates the executable
#read any rule as "file it concerns : dependencies \n\t instruction"
main: main.o $(OBJ)
	$(CC) $^ -o $(EXEC) $(LINKER_FLAGS)
#$^ = list of all dependencies, S@ = the name of the rule
main.o: main.cpp Objects/objects.h
	$(CC) $(CFLAGS) -o $@ -c $< 
#$< = name of the first dependency
%.o: %.cpp Objects/objects.h #generic rule. For any file ending in .o that doesn't have a rule defined (like main)
	$(CC) $(CFLAGS) -o $@ -c $< 
#it depends on its own cpp and the objects header

#auxiliary commands for deleting .o files and the executable. Good for testing, good for certifying compilation of all files
#.PHONY allows you to call make for a specific command without it having to verify any files, otherwise, it'd check for a "clean" file
#on a 'make clean' call
.PHONY: clean mrproper 
#deletes all .o files
clean: 
	rm -rf *.o
	@cd Objects && $(MAKE) $@
#"cd Objects" goes inside the Objects folder, "&& $(MAKE) $@" calls the makefile inside with the command given
#deletes the executable
mrproper: clean
	rm -rf $(EXEC)
	@cd Objects && $(MAKE) $@