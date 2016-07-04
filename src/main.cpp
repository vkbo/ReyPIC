/**
 * ReyPIC – Main File
 */

// Core Header Files
#include "build.hpp"
#include "config.hpp"
#include "functions.hpp"

// Classes
#include "clsSimulation.hpp"
#include "clsInput.hpp"
#include "clsSpecies.hpp"
#include "clsGrid.hpp"

using namespace std;
using namespace reypic;

int abortExec(int);

/**
 * Main Program Loop
 */

int main(int argc, char* argv[]) {

    // Variables
    error_t errMPI;
    int     iRank;
    bool    isMaster = false;

   /**
    *  Initialise
    */

    errMPI = MPI_Init(&argc, &argv);
    if(errMPI != MPI_SUCCESS) {
        return abortExec(ERR_MPI_INIT);
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &iRank);
    isMaster = (iRank == 0);

    // Write output header
    if(isMaster) {
        printf("\n");
        printf("  ReyPIC – 3D Particle in Cell\n");
        printf(" ******************************\n");
        printf("  Version: %s\n", BUILD);
        printf("\n");
    }

    // Check that there is a minimum of one argument
    if(argc < 2) {
        if(isMaster) {
            printf("  ERROR: No input file specified\n");
        }
        return abortExec(ERR_USAGE);
    }

   /**
    *  Simulation Setup
    */

    Simulation Sim;
    error_t errSim = ERR_NONE;

    // Parse input options and set input file
    for(int i=1; i<argc; i++) {
        if(strcmp(argv[i], "-t")  == 0) Sim.setRunMode(RUN_MODE_TEST);
        if(strcmp(argv[i], "-tt") == 0) Sim.setRunMode(RUN_MODE_EXT_TEST);
    }
    Sim.setInputFile(argv[argc-1]);

    // Read input file
    errSim = Sim.ReadInput();
    if(errSim != ERR_NONE) {
        return abortExec(errSim);
    }

    // Set up simulation
    errSim = Sim.Setup();
    if(errSim != ERR_NONE) {
        return abortExec(errSim);
    }

   /**
    * THE END!
    */

    MPI_Finalize();

    return ERR_NONE;
}

// ********************************************************************************************** //

/**
 * Abort Execution
 */

int abortExec(int errVal) {

    int iRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &iRank);

    if(iRank == 0) {

        printf("\n");
        printf("  ReyPIC exectuion aborted with error code %d:\n", errVal);

        switch(errVal) {
            case ERR_ANY:       printf("    General error\n"); break;
            case ERR_USAGE:     printf("    Usage error\n"); break;
            case ERR_MPI_INIT:  printf("    MPI initialization error\n"); break;
            case ERR_INPUTFILE: printf("    Input file error\n"); break;
            case ERR_INPUTVAR:  printf("    Input variable error\n"); break;
            case ERR_SETUP:     printf("    Setup error\n"); break;
            case ERR_INIT:      printf("    Initialization error\n"); break;
            case ERR_EXEC:      printf("    Execution error\n"); break;
            case ERR_DIAG:      printf("    Diagnostics error\n"); break;
        }

        printf("\n");
    }

    MPI_Finalize();

    return errVal;
}

// ********************************************************************************************** //

// End Main
