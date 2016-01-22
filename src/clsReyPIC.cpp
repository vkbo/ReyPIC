/**
 * ReyPIC – ReyPIC Core Source
 */

#include "clsReyPIC.hpp"

using namespace reypic;

ReyPIC::ReyPIC() {

    // Default Values
    RunMode = RUN_MODE_FULL;

    return;
}

/**
 * Setters
 */

bool ReyPIC::SetInputFile(char* cFile) {

    if(FileExists(cFile)) {
        InputFile = cFile;
        return true;
    } else {
        return false;
    }
}

bool ReyPIC::SetRunMode(int iRunMode) {

    switch(iRunMode) {
        case RUN_MODE_TEST:
            RunMode = RUN_MODE_TEST;
            return true;
            break;
        case RUN_MODE_FULL:
            RunMode = RUN_MODE_FULL;
            return true;
            break;
    }

    return false;
}

/**
 * Tools
 */

bool FileExists(const char* cFile) {
    return (access(cFile, F_OK) != -1);
}
