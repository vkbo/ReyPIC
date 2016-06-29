/**
 * ReyPIC – Functions Header
 */

#ifndef MAIN_FUNCTIONS
#define MAIN_FUNCTIONS

#include "config.hpp"

namespace m {

    void     linspace(double_t, double_t, int32_t, double_t*);
    double_t min(double_t*, int32_t);
    double_t max(double_t*, int32_t);
    double_t minind(double_t*, int32_t, int32_t*);
    double_t maxind(double_t*, int32_t, int32_t*);
    double_t sum(double_t*, int32_t);
    double_t avg(double_t*, int32_t);
    void     scale(double_t*, int32_t, double_t);
    void     offset(double_t*, int32_t, double_t);

} // End namespace

#endif
