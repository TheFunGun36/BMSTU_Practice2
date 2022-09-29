#include "Real.h"
#include <cmath>

bool real_eq(real a, real b, real tolerance) {
    return abs(a - b) <= tolerance;
}

real real_clamp(real val, real min_val, real max_val) {
    return val < min_val ? min_val : (val > max_val ? max_val : val);
}

real real_min(real a, real b) {
    return a < b ? a : b;
}

real real_max(real a, real b) {
    return a > b ? a : b;
}
