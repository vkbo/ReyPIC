###
###  Makefile for ReyPIC
###

CC      = mpic++
DEBUG   = -g -Wall
CFLAGS  = $(DEBUG) -std=c++11 -march=native -O4 -c
LFLAGS  = $(DEBUG)

SRC     = src
BUILD   = build
OUTPUT  = bin

EXEC    = reypic.e
VERSION = $(shell git describe | tr -d gv)

HEADERS = config.hpp functions.hpp
GLOBAL  = $(addprefix $(SRC)/,$(HEADERS))

CLASSES = clsInput.o clsSimulation.o clsPhysics.o clsTime.o clsMath.o clsSpecies.o clsGrid.o
OBJECTS = $(addprefix $(BUILD)/,$(CLASSES))

##
## Compile
##

# Check if build and bin directories exists
$(shell [ -d "$(BUILD)" ] || mkdir -p $(BUILD))
$(shell [ -d "$(OUTPUT)" ] || mkdir -p $(OUTPUT))
$(shell echo "#define BUILD \"$(VERSION)\"" > $(SRC)/build.hpp)

# Executable
$(EXEC) : $(BUILD)/main.o $(BUILD)/functions.o $(OBJECTS)
	$(CC) $(LFLAGS) $(BUILD)/main.o $(BUILD)/functions.o $(OBJECTS) $(LIBFLAGS) -o $@

# Core Files

$(BUILD)/main.o : $(SRC)/main.cpp $(SRC)/build.hpp $(GLOBAL)
	$(CC) $(CFLAGS) $(SRC)/main.cpp -o $@

$(BUILD)/functions.o : $(SRC)/functions.cpp $(GLOBAL)
	$(CC) $(CFLAGS) $(SRC)/functions.cpp -o $@

# Classes

$(BUILD)/clsInput.o : $(SRC)/clsInput.cpp $(SRC)/clsInput.hpp $(GLOBAL)
	$(CC) $(CFLAGS) $(SRC)/clsInput.cpp -o $@

$(BUILD)/clsSimulation.o : $(SRC)/clsSimulation.cpp $(SRC)/clsSimulation.hpp $(SRC)/clsInput.hpp $(SRC)/clsTime.hpp $(SRC)/clsGrid.hpp $(SRC)/clsSpecies.hpp $(GLOBAL)
	$(CC) $(CFLAGS) $(SRC)/clsSimulation.cpp -o $@

$(BUILD)/clsPhysics.o : $(SRC)/clsPhysics.cpp $(SRC)/clsPhysics.hpp $(SRC)/clsInput.hpp $(GLOBAL)
	$(CC) $(CFLAGS) $(SRC)/clsPhysics.cpp -o $@

$(BUILD)/clsTime.o : $(SRC)/clsTime.cpp $(SRC)/clsTime.hpp $(SRC)/clsInput.hpp $(GLOBAL)
	$(CC) $(CFLAGS) $(SRC)/clsTime.cpp -o $@

$(BUILD)/clsMath.o : $(SRC)/clsMath.cpp $(SRC)/clsMath.hpp $(GLOBAL)
	$(CC) $(CFLAGS) $(SRC)/clsMath.cpp -o $@

$(BUILD)/clsSpecies.o : $(SRC)/clsSpecies.cpp $(SRC)/clsSpecies.hpp $(SRC)/clsInput.hpp $(SRC)/clsGrid.hpp $(SRC)/clsMath.hpp $(GLOBAL)
	$(CC) $(CFLAGS) $(SRC)/clsSpecies.cpp -o $@

$(BUILD)/clsGrid.o : $(SRC)/clsGrid.cpp $(SRC)/clsGrid.hpp $(SRC)/clsInput.hpp $(SRC)/clsMath.hpp $(GLOBAL)
	$(CC) $(CFLAGS) $(SRC)/clsGrid.cpp -o $@

# Make Clean

clean:
	rm $(BUILD)/* $(EXEC)
