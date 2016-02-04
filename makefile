###
###  Makfeile for ReyPIC
###

CC      = g++
DEBUG   = -g -Wall
CFLAGS  = $(DEBUG) -std=c++11 -O2 -c
LFLAGS  = $(DEBUG)

SRC     = src
BUILD   = build
OUTPUT  = bin

EXEC    = reypic.e
MAIN    = $(SRC)/main.cpp
VERSION = $(shell git describe)

CLASSES = clsSimulation.o clsInput.o clsSpecies.o clsGrid.o
OBJECTS = $(addprefix $(BUILD)/,$(CLASSES))

##
## Compile
##

# Check if build and bin directories exists
$(shell [ -d "$(BUILD)" ] || mkdir -p $(BUILD))
$(shell [ -d "$(OUTPUT)" ] || mkdir -p $(OUTPUT))
$(shell echo "#define BUILD \"$(VERSION)\"" > $(SRC)/build.hpp)

# Executable
$(EXEC) : $(BUILD)/main.o $(OBJECTS) $(BNOFILE) $(SRC)/build.hpp
	$(CC) $(LFLAGS) $(BUILD)/main.o $(OBJECTS) $(LIBFLAGS) -o $@

# Core Files

$(BUILD)/main.o : $(MAIN) $(SRC)/build.hpp
	$(CC) $(CFLAGS) $(MAIN) -o $@

$(BUILD)/clsSimulation.o : $(SRC)/clsSimulation.cpp $(SRC)/clsSimulation.hpp
	$(CC) $(CFLAGS) $(SRC)/clsSimulation.cpp -o $@

# Classes

$(BUILD)/clsInput.o : $(SRC)/clsInput.cpp $(SRC)/clsInput.hpp
	$(CC) $(CFLAGS) $(SRC)/clsInput.cpp -o $@

$(BUILD)/clsSpecies.o : $(SRC)/clsSpecies.cpp $(SRC)/clsSpecies.hpp
	$(CC) $(CFLAGS) $(SRC)/clsSpecies.cpp -o $@

$(BUILD)/clsGrid.o : $(SRC)/clsGrid.cpp $(SRC)/clsGrid.hpp
	$(CC) $(CFLAGS) $(SRC)/clsGrid.cpp -o $@

# Make Clean

clean:
	rm $(BUILD)/* $(EXEC)
