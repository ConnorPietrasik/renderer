#include "objects/RecursiveTetrahedron.h"
#include "math/Point.h"
#include "math/math.h"

#include <iostream>

//From http://blog.hvidtfeldts.net/index.php/2011/08/distance-estimated-3d-fractals-iii-folding-space/,
//NOT CURRENTLY WORKING, gave up on this until later, in TODO list
double RecursiveTetrahedron::sdf(const Point& p) {
	Point offset;
	Point math = p;
	float scale = 2;

	float dist, d;
	for (int i = 0; i < iterations; i++) {
		offset = { 1, 1, 1 };
		dist = (p - Point(1, 1, 1)).magnitude();

		d = (p - Point(-1, -1, 1)).magnitude();
		if (d < dist) {
			offset = { -1, -1, 1 };
			dist = d;
		}

		d = (p - Point(1, -1, -1)).magnitude();
		if (d < dist) {
			offset = { 1, -1, -1 };
			dist = d;
		}

		d = (p - Point(-1, 1, -1)).magnitude();
		if (d < dist) {
			offset = { -1, 1, -1 };
			dist = d;
		}

		math = (math * scale) - (offset * (scale - 1.0));
	}

	double ret = ((Vector)math).magnitude() * math::pow(scale, -iterations);
	//if (ret < 100) std::cout << p << '\t' <<  ret << '\n';

	return ret;
}