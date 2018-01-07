#makefile for phylotoy

CC = g++
DEBUG = -g
CCFLAGS = -Wall -Wextra -ansi -pedantic $(DEBUG)
LFLAGS = -Wall -Wextra -ansi -pedantic $(DEBUG)

EXEC = phylotoy
SOURCES = $(wildcard ./src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
 
# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)


