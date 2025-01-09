#pragma once

#include "objects/Object.h"
#include "math/raymarch.h"

class RecursiveTetrahedron : public Object {
	int iterations;
	Color test = { 478, 0, 1 };	//TEMP

public:
	RecursiveTetrahedron(int iterations) : iterations(iterations) {}

	double intersects(Ray ray) { return -1; }
	double sdf(const Point& p);

	//Temp values
	Color& getColor() { return test; }
	Color& getSpecularColor() { return test; }
	float getShininess() { return 0; }
	float getReflectivity() { return 0; }

	Vector getNormal(const Point& touched) { return raymarch::getNormalRM(touched, this); }
};