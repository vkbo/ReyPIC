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

    // Set Defaults
    int   iRunMode = RUN_MODE_FULL;
    int   iErr = 0;
    char* cInputFile;

    // Write Output Header
    cout << endl;
    cout << "  ReyPIC  " << endl;
    cout << " ********" << endl;
    cout << endl;
    cout << "  Version: " << VERSION << "-R" << REVISION << endl;
    cout << "  Build:   " << BUILD_NO+1 << endl;
    cout << "  Date:    " << BUILD_DATE << endl;
    cout << endl;

    // Parse Input Options
    for(int i=1; i<argc; i++) {

        // Running in Test Mode
        if(strcmp(argv[i], "-t")) {
            iRunMode = RUN_MODE_TEST;
        }

        // Input File
        if(strcmp(argv[i], "-i")) {
            if(i < argc-1) {
                cInputFile = argv[i+1];
                i++;
            } else {
                cout << "  ERROR: Input file must follow switch -i" << endl;
                iErr++;
            }
        } else {
            cout << "  ERROR: No input file specified" << endl;
            iErr++;
        }
    }

    if(iErr > 0) {
        cout << endl;
        cout << "  Errors encountered. Aborting ..." << endl;
        cout << endl;
        return ERR_INIT;
    }

    return ERR_NONE;
}
