/**
 * ReyPIC – Main Config
 */

#ifndef RP_CONFIG
#define RP_CONFIG

// Includes
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>
#include <array>
#include <vector>

// Run Modes
#define RUN_MODE_TEST 1
#define RUN_MODE_FULL 2

// Error Modes
#define ERR_NONE     0
#define ERR_INIT     80
#define ERR_MPI_INIT 81
#define ERR_INPUT    82
#define ERR_SETUP    83
#define ERR_EXEC     84
#define ERR_DIAG     85

// Input File Sections
#define INPUT_NONE    0
#define INPUT_SIM     1
#define INPUT_EMF     2
#define INPUT_SPECIES 3

#endif
