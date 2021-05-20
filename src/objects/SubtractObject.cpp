#include "objects/SubtractObject.h"

double SubtractObject::sdf(const Point& p) { //More or less from https://iquilezles.org/www/articles/distfunctions/distfunctions.htm
	float max = -100000;
	for (auto& sub : subtractors) {
		float tmp = math::max(main->sdf(p), -sub->sdf(p));
		if (tmp > max) max = tmp;
	}

	return max;
}