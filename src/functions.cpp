/**
 * ReyPIC – Functions Source
 */

#include "config.hpp"
#include "functions.hpp"

using namespace std;

void reypic::linspace(double valMin, double valMax, int nVal, double* aReturn) {

    double valSpan = valMax - valMin;
    double delVal  = valSpan/(nVal-1);

    for(int i=0; i<nVal; i++) {
        aReturn[i] = i*delVal + valMin;
    }

    return;
}
