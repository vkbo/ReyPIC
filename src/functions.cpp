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

void m::linspace(double valMin, double valMax, int nVal, double* aReturn) {

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
 *  Returns minimum value from array aData with length nData
 */

double m::min(double* aData, int nData) {

    double valMin = aData[0];

    for(int i=1; i<nData; i++) {
        if(aData[i] < valMin) {
            valMin = aData[i];
        }
    }

    return valMin;
}

// ********************************************************************************************** //

/**
 *  Max Value
 * ===========
 *  Return maximum value from array aData with length nData
 */

double m::max(double* aData, int nData) {

    double valMax = aData[0];

    for(int i=1; i<nData; i++) {
        if(aData[i] > valMax) {
            valMax = aData[i];
        }
    }

    return valMax;
}

// ********************************************************************************************** //

/**
 *  Min Value with Index
 * ======================
 *  Returns minimum value and index indMin from array aData with length nData
 */

double m::minind(double* aData, int nData, int* indMin) {

    double valMin = aData[0];
          *indMin = 0;

    for(int i=1; i<nData; i++) {
        if(aData[i] < valMin) {
             valMin = aData[i];
            *indMin = i;
        }
    }

    return valMin;
}

// ********************************************************************************************** //

/**
 *  Max Value with Index
 * ======================
 *  Returns maximum value and index indMax from array aData with length nData
 */

double m::maxind(double* aData, int nData, int* indMax) {

    double valMax = aData[0];
          *indMax = 0;

    for(int i=1; i<nData; i++) {
        if(aData[i] > valMax) {
             valMax = aData[i];
            *indMax = i;
        }
    }

    return valMax;
}

// ********************************************************************************************** //

/**
 *  Sum
 * ======
 *  Returns sum of array aData with length nData
 */

double m::sum(double* aData, int nData) {

    double valSum = 0.0;

    for(int i=0; i<nData; i++) {
        valSum += aData[i];
    }

    return valSum;
}

// ********************************************************************************************** //

/**
 *  Average Value
 * ===============
 *  Returns average value valAvg from array aData with length nData
 */

double m::avg(double* aData, int nData) {

    double valSum = 0.0;

    for(int i=0; i<nData; i++) {
        valSum += aData[i];
    }

    return valSum/nData;
}

// ********************************************************************************************** //

/**
 *  Scale Array
 * =============
 *  Scales an array aData with length nData by a value valScale
 */

void m::scale(double* aData, int nData, double valScale) {

    for(int i=0; i<nData; i++) {
        aData[i] *= valScale;
    }

    return;
}

// ********************************************************************************************** //

/**
 *  Offset Array
 * ==============
 *  Offsets an array aData with length nData by a value valScale
 */

void m::offset(double* aData, int nData, double valOffset) {

    for(int i=0; i<nData; i++) {
        aData[i] += valOffset;
    }

    return;
}

// ********************************************************************************************** //
