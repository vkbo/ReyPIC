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
BNOFILE = $(SRC)/build.txt

CLASSES = clsSpecies.o
OBJECTS = $(addprefix $(BUILD)/,$(CLASSES))

##
## Compile
##

# Check if build and bin directories exists
$(shell [ -d "$(BUILD)" ] || mkdir -p $(BUILD))
$(shell [ -d "$(OUTPUT)" ] || mkdir -p $(OUTPUT))

# Executable
$(EXEC) : $(BUILD)/main.o $(OBJECTS) $(BNOFILE) $(SRC)/build.hpp
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

# Build number file.  Increment if any object file changes.
$(BNOFILE): $(BUILD)/main.o $(OBJECTS)
	@if ! test -f $(BNOFILE); then echo 0 > $(BNOFILE); fi
	@echo $$(($$(cat $(BNOFILE)) + 1)) > $(BNOFILE)
	@echo \#define BUILD_NO $$(($$(cat $(BNOFILE))))    > $(SRC)/build.hpp
	@echo \#define BUILD_DATE $$(($$(date +'%Y%m%d'))) >> $(SRC)/build.hpp
