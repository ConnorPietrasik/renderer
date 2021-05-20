#include "objects/UnionObject.h"

double UnionObject::sdf(const Point& p) { //https://iquilezles.org/www/articles/distfunctions/distfunctions.htm
	float min = 1000000;
	for (auto& obj : objects) {
		float temp = obj->sdf(p);
		if (temp < min) min = temp;
	}
	return min;
}