/**
 * ReyPIC – Main File
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>

// Core Header Files
#include "build.hpp"
#include "config.hpp"
#include "clsReyPIC.hpp"

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
    ReyPIC* oRP = new ReyPIC();

    // Set Defaults
    int iErr = 0;

    // Write Output Header
    printf("\n");
    printf("  ReyPIC\n");
    printf(" *********\n");
    printf("\n");
    printf("  Version: %s-R%03d Build %d\n", VERSION, REVISION, BUILD_NO+1);
    printf("\n");

    // Parse Input Options
    for(int i=1; i<argc; i++) {

        // Running in Test Mode
        if(strcmp(argv[i], "-t") == 0) {
            printf("  Running in test mode.\n");
            oRP->SetRunMode(RUN_MODE_TEST);
        }

        // Input File
        if(strcmp(argv[i], "-i") == 0) {
            if(i+1 < argc) {
                printf("  Input file: %s\n", argv[i+1]);
                oRP->SetInputFile(argv[i+1]);
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

    return ERR_NONE;
}
