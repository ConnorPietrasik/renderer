#pragma once
#include "Point.h"

struct Light {
	Point pos;
	Color ambient;
	Color diffuse;
	Color specular;
	double radius;
};