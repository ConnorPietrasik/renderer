#include "math/math.h"



double math::pow(double x, int n) {
	if (n == 0) return 1;
	double ret = x;
	if (n > 0) {
		for (int i = 0; i < n - 1; i++) {
			ret *= x;
		}
		return ret;
	}
	else {
		for (int i = 0; i < -n - 1; i++) {
			ret *= x;
		}
		return 1 / ret;
	}
}