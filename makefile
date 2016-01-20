###
###  Makfeile for ReyPIC
###

CC      = g++
DEBUG   = -g -Wall
CFLAGS  = $(DEBUG) -O2 -c
LFLAGS  = $(DEBUG)

SRC     = src
BUILD   = build
OUTPUT  = bin

EXEC    = reypic.e
MAIN    = $(SRC)/main.cpp

CLASSES = clsSpecies.o
OBJECTS = $(addprefix $(BUILD)/,$(CLASSES))

##
## Compile
##

# Check if build and bin directories exists
$(shell [ -d "$(BUILD)" ] || mkdir -p $(BUILD))
$(shell [ -d "$(OUTPUT)" ] || mkdir -p $(OUTPUT))

# Executable
$(EXEC) : $(BUILD)/main.o $(OBJECTS)
	$(CC) $(LFLAGS) $(BUILD)/main.o $(OBJECTS) $(LIBFLAGS) -o $@

# Main File

$(BUILD)/main.o : $(MAIN)
	$(CC) $(CFLAGS) $(MAIN) -o $@

# Classes

$(BUILD)/clsSpecies.o : $(SRC)/clsSpecies.cpp $(SRC)/clsSpecies.hpp
	$(CC) $(CFLAGS) $(SRC)/clsSpecies.cpp -o $@

# Make Clean

clean:
	rm $(BUILD)/* $(EXEC)
