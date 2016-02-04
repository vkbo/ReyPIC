/**
 * ReyPIC – Main File
 */

// Core Header Files
#include "build.hpp"
#include "config.hpp"
#include "clsSimulation.hpp"

// Classes
#include "clsInput.hpp"
#include "clsSpecies.hpp"
#include "clsGrid.hpp"

using namespace std;
using namespace reypic;

/**
 * Main Program Loop
 */
    
int main(int argc, char* argv[]) {

    // Init
    Simulation* oSim = new Simulation();

    // Set Defaults
    int iErr = 0;

    // Write Output Header
    printf("\n");
    printf("  ReyPIC\n");
    printf(" *********\n");
    printf("\n");
    printf("  Version: %s\n", BUILD);
    printf("\n");

    // Parse Input Options
    for(int i=1; i<argc; i++) {

        // Running in Test Mode
        if(strcmp(argv[i], "-t") == 0) {
            printf("  Running in test mode.\n");
            oSim->setRunMode(RUN_MODE_TEST);
        }

        // Input File
        if(strcmp(argv[i], "-i") == 0) {
            if(i+1 < argc) {
                printf("  Input file: %s\n", argv[i+1]);
                oSim->setInputFile(argv[i+1]);
            } else {
                printf("  ERROR: Input file must follow switch -i\n");
                iErr++;
            }
        }
    }
    printf("\n");

    if(iErr > 0) {
        printf("  Errors encountered. Aborting ...\n");
        printf("\n");
        return ERR_INIT;
    }

    /**
     *  Simulation Setup
     */

    oSim->ReadInput();

    return ERR_NONE;
}
