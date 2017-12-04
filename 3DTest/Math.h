#pragma once
#include <math.h>

namespace Math {
	const double pi = 3.14159265358979323846264338327950288;
	const float pi_over_180 = (float)pi / 180.f;
}

inline float sindeg(float degrees) { return sinf(degrees * Math::pi_over_180); };
inline float cosdeg(float degrees) { return cosf(degrees * Math::pi_over_180); };
