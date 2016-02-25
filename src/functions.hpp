/**
 * ReyPIC – Functions Header
 */

#ifndef MAIN_FUNCTIONS
#define MAIN_FUNCTIONS

#include "config.hpp"

namespace m {

    void   linspace(double, double, int, double*);
    double min(double*, int);
    double max(double*, int);
    double minind(double*, int, int*);
    double maxind(double*, int, int*);
    double sum(double*, int);
    double avg(double*, int);
    void   scale(double*, int, double);
    void   offset(double*, int, double);

} // End namespace

#endif
