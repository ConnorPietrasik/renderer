#pragma once

namespace math {
	//Returns x^n
	double pow(double x, int n);

	//NEW
	//Returns X if it's between min and max, otherwise returns min or max
	double clamp(double x, double min, double max);

	//NEW
	//Returns the sign of the given number (-1, 0, 1)
	int sign(double x);
}

