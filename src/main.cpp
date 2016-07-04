/**
 * ReyPIC – Main File
 */

// Core Header Files
#include "build.hpp"
#include "config.hpp"
#include "functions.hpp"

// Classes
#include "clsInput.hpp"
#include "clsSimulation.hpp"
#include "clsTime.hpp"
#include "clsGrid.hpp"
#include "clsPhysics.hpp"

using namespace std;
using namespace reypic;

error_t abortExec(error_t);

/**
 * Main Program Loop
 */

int main(int argc, char* argv[]) {

    error_t    errVal;
    int        iRank;
    bool       isMaster = false;

    Input      simInput;
    Simulation simSim;
    Time       simTime;
    Grid       simGrid;
    Physics    simPhys;

   /**
    *  Initialise MPI
    */

    errVal = MPI_Init(&argc, &argv);
    if(errVal != MPI_SUCCESS) {
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

    // Read input file
    simInput.ReadFile(argv[argc-1]);
    if(errVal != ERR_NONE) {
        return abortExec(errVal);
    }

   /**
    *  Run Setups
    */

    for(int i=1; i<argc; i++) {
        if(strcmp(argv[i], "-t")  == 0) simSim.setRunMode(RUN_MODE_TEST);
        if(strcmp(argv[i], "-tt") == 0) simSim.setRunMode(RUN_MODE_EXT_TEST);
    }

    // Simulation
    errVal = simSim.Setup(&simInput);
    if(errVal != ERR_NONE) {
        return abortExec(errVal);
    }

    // Time
    errVal = simTime.Setup(&simInput);
    if(errVal != ERR_NONE) {
        return abortExec(errVal);
    }

    // Grid
    errVal = simTime.Setup(&simInput);
    if(errVal != ERR_NONE) {
        return abortExec(errVal);
    }

    // Physics
    errVal = simPhys.Setup(&simInput);
    if(errVal != ERR_NONE) {
        return abortExec(errVal);
    }

   /**
    *  THE END!
    */

    //delete[] simInput;
    //delete[] simSim;
    //delete[] simTime;
    //delete[] simGrid;
    //delete[] simPhys;

    MPI_Finalize();

    return ERR_NONE;
}

// ********************************************************************************************** //

/**
 *  Abort Execution
 */

error_t abortExec(int errVal) {

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
