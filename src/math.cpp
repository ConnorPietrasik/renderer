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