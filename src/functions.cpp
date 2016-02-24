/**
 * ReyPIC – Functions Source
 */

#include "config.hpp"
#include "functions.hpp"

using namespace std;

// ********************************************************************************************** //

/**
 *  Linspace
 * ==========
 *  Generayes array aReturn of length nVal from valMin to valMax
 */

void reypic::linspace(double valMin, double valMax, int nVal, double* aReturn) {

    double valSpan = valMax - valMin;
    double delVal  = valSpan/(nVal-1);

    for(int i=0; i<nVal; i++) {
        aReturn[i] = i*delVal + valMin;
    }

    return;
}

// ********************************************************************************************** //

/**
 *  Min Value
 * ===========
 *  Gives minimum value valMin and index indMin from array aData with length nData
 */

void reypic::min(double* aData, int nData, double* valMin, int* indMin) {

    *valMin = aData[0];
    *indMin = 0;

    for(int i=1; i<nData; i++) {
        if(aData[i] < *valMin) {
            *valMin = aData[i];
            *indMin = i;
        }
    }

    return;
}

// ********************************************************************************************** //

/**
 *  Max Value
 * ===========
 *  Gives maximum value valMax and index indMax from array aData with length nData
 */

void reypic::max(double* aData, int nData, double* valMax, int* indMax) {

    *valMax = aData[0];
    *indMax = 0;

    for(int i=1; i<nData; i++) {
        if(aData[i] > *valMax) {
            *valMax = aData[i];
            *indMax = i;
        }
    }

    return;
}

// ********************************************************************************************** //
