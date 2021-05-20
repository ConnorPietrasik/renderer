#include "objects/IntersectObject.h"

double IntersectObject::sdf(const Point& p) { //More or less from https://iquilezles.org/www/articles/distfunctions/distfunctions.htm
	float max = -100000;
	for (auto& obj : objects) {
		float tmp = obj->sdf(p);
		if (tmp > max) max = tmp;
	}

	return max;
}