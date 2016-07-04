/**
 * ReyPIC – Main File
 */

// Core Header Files
#include "build.hpp"
#include "config.hpp"
#include "functions.hpp"

// Classes
#include "clsSimulation.hpp"
#include "clsTime.hpp"
#include "clsInput.hpp"
#include "clsSpecies.hpp"
#include "clsGrid.hpp"

using namespace std;
using namespace reypic;

int picLoop(Simulation*);
int abortExec(int);

/**
 * Main Program Loop
 */

int main(int argc, char* argv[]) {

    // Variables
    Simulation *picSim = new Simulation();
    int         iRank;
    bool        isMaster = false;
    error_t     errMPI   = ERR_NONE;
    error_t     errSim   = ERR_NONE;
    error_t     errLoop  = ERR_NONE;

   /**
    * Initialise
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
    * Simulation Setup
    */

    // Parse input options and set input file
    //for(int i=1; i<argc; i++) {
    //    if(strcmp(argv[i], "-t")  == 0) picSim->setRunMode(RUN_MODE_TEST);
    //    if(strcmp(argv[i], "-tt") == 0) picSim->setRunMode(RUN_MODE_EXT_TEST);
    //}
    //picSim->setInputFile(argv[argc-1]);

    // Read input file
    //errSim = picSim->ReadInput();
    //if(errSim != ERR_NONE) {
    //    return abortExec(errSim);
    //}

    // Set up simulation
    //errSim = picSim->Setup();
    //if(errSim != ERR_NONE) {
    //    return abortExec(errSim);
    //}

   /**
    * Main Loop
    */

    //errLoop = picLoop(picSim);
    //if(errLoop != ERR_NONE) {
    //    return abortExec(errLoop);
    //}

   /**
    * THE END!
    */

    //delete[] picSim;
    MPI_Finalize();

    return ERR_NONE;
}

// ********************************************************************************************** //

/**
 * Main Loop
 */

int picLoop(Simulation* picSim) {

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
