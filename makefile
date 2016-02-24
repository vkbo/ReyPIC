###
###  Makfeile for ReyPIC
###

CC      = mpic++
DEBUG   = -g -Wall
CFLAGS  = $(DEBUG) -std=c++11 -march=native -O4 -c
LFLAGS  = $(DEBUG)

SRC     = src
BUILD   = build
OUTPUT  = bin

EXEC    = reypic.e
VERSION = $(shell git describe | tr -d v)

HEADERS = config.hpp functions.hpp
GLOBAL  = $(addprefix $(SRC)/,$(HEADERS))

CLASSES = clsSimulation.o clsMath.o clsInput.o clsSpecies.o clsGrid.o
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

$(BUILD)/clsSimulation.o : $(SRC)/clsSimulation.cpp $(SRC)/clsSimulation.hpp $(GLOBAL)
	$(CC) $(CFLAGS) $(SRC)/clsSimulation.cpp -o $@

$(BUILD)/clsMath.o : $(SRC)/clsMath.cpp $(SRC)/clsMath.hpp $(GLOBAL)
	$(CC) $(CFLAGS) $(SRC)/clsMath.cpp -o $@

$(BUILD)/clsInput.o : $(SRC)/clsInput.cpp $(SRC)/clsInput.hpp $(GLOBAL)
	$(CC) $(CFLAGS) $(SRC)/clsInput.cpp -o $@

$(BUILD)/clsSpecies.o : $(SRC)/clsSpecies.cpp $(SRC)/clsSpecies.hpp $(GLOBAL)
	$(CC) $(CFLAGS) $(SRC)/clsSpecies.cpp -o $@

$(BUILD)/clsGrid.o : $(SRC)/clsGrid.cpp $(SRC)/clsGrid.hpp $(GLOBAL)
	$(CC) $(CFLAGS) $(SRC)/clsGrid.cpp -o $@

# Make Clean

clean:
	rm $(BUILD)/* $(EXEC)
