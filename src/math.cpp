#include "math.h"



double math::pow(double x, int n) {
	if (n == 0) return 1;
	double ret = x;
	if (n > 0) {
		for (int i = 0; i < n - 1; i++) {
			ret *= x;
		}
	}
	else {
		for (int i = 0; i < -n - 1; i++) {
			ret *= x;
		}
		ret = 1 / ret;
	}
	return ret;
}

double math::clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

int math::sign(double x) {
	double eps = 0.00000001;
	if (x > eps) return 1;
	if (x < -eps) return -1;
	return 0;
}