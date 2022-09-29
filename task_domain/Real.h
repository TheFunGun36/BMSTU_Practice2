#pragma once

using real = double;
bool real_eq(real a, real b, real tolerance = 1e-10);
real real_clamp(real val, real min_val, real max_val);
real real_min(real a, real b);
real real_max(real a, real b);
