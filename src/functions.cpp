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

void m::linspace(double_t valMin, double_t valMax, int32_t nVal, double_t* aReturn) {

    double_t valSpan = valMax - valMin;
    double_t delVal  = valSpan/(nVal-1);

    for(int32_t i=0; i<nVal; i++) {
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

double_t m::min(double_t* aData, int32_t nData) {

    double_t valMin = aData[0];

    for(int32_t i=1; i<nData; i++) {
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

double_t m::max(double_t* aData, int32_t nData) {

    double_t valMax = aData[0];

    for(int32_t i=1; i<nData; i++) {
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

double_t m::minind(double_t* aData, int32_t nData, int32_t* indMin) {

    double_t valMin = aData[0];
            *indMin = 0;

    for(int32_t i=1; i<nData; i++) {
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

double_t m::maxind(double_t* aData, int32_t nData, int32_t* indMax) {

    double_t valMax = aData[0];
            *indMax = 0;

    for(int32_t i=1; i<nData; i++) {
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

double_t m::sum(double_t* aData, int32_t nData) {

    double_t valSum = 0.0;

    for(int32_t i=0; i<nData; i++) {
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

double_t m::avg(double_t* aData, int32_t nData) {

    double_t valSum = 0.0;

    for(int32_t i=0; i<nData; i++) {
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

void m::scale(double_t* aData, int32_t nData, double_t valScale) {

    for(int32_t i=0; i<nData; i++) {
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

void m::offset(double_t* aData, int32_t nData, double_t valOffset) {

    for(int32_t i=0; i<nData; i++) {
        aData[i] += valOffset;
    }

    return;
}

// ********************************************************************************************** //
