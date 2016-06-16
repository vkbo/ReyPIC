/**
 *  ReyPIC – Main Config
 * ======================
 *  Version 0.0.1 – Pre-release with working input file reader
 */

#ifndef RP_CONFIG
#define RP_CONFIG

// Includes
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <array>
#include <vector>
#include <mpi.h>

// TypeDefs
typedef std::vector<std::vector<double_t> > vvdouble_t;
typedef std::vector<std::string>            vstring_t;
typedef std::vector<double_t>               vdouble_t;
typedef std::vector<int32_t>                vint_t;
typedef std::string                         string_t;
typedef uint64_t                            index_t;
typedef int16_t                             value_t;

// Run Modes
#define RUN_MODE_FULL      1
#define RUN_MODE_TEST      2
#define RUN_MODE_EXT_TEST  3

// Error Modes
#define ERR_NONE           0
#define ERR_ANY            1
#define ERR_USAGE         80
#define ERR_MPI_INIT      81
#define ERR_INPUTFILE     82
#define ERR_INPUTVAR      83
#define ERR_SETUP         84
#define ERR_INIT          85
#define ERR_EXEC          86
#define ERR_DIAG          87

// Input File Sections
#define INPUT_NONE         0
#define INPUT_CONF         1
#define INPUT_SIM          2
#define INPUT_GRID         3
#define INPUT_EMF          4
#define INPUT_SPECIES      5

// Input File Types
#define INVAR_INT          1
#define INVAR_DOUBLE       2
#define INVAR_STRING       3
#define INVAR_VINT         4
#define INVAR_VDOUBLE      5
#define INVAR_VSTRING      6

// Momentum Variables
#define MOM_NONE           0
#define MOM_THERMAL        1
#define MOM_TWISS          2

#endif
