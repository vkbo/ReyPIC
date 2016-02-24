/**
 * ReyPIC – Functions Header
 */

#ifndef MAIN_FUNCTIONS
#define MAIN_FUNCTIONS

#include "config.hpp"

namespace m {

    void   linspace(double, double, int, double*);
    void   min(double*, int, double*, int*);
    void   max(double*, int, double*, int*);
    double sum(double*, int);
    double avg(double*, int);
    void   scale(double*, int, double);
    void   offset(double*, int, double);

} // End namespace

#endif
