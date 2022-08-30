#include "Real.h"
#include <cmath>

bool real_eq(real a, real b) { return abs(a - b) <= 1e-10; }
