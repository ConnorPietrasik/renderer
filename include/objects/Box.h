#pragma once

#include "objects/Object.h"

class Box : public Object {
	Point dimensions;

	Color normalColor;
	Color specularColor;
	float shininess;
	float reflectivity;

public:
	//Makes a box with the given dimensions, negative dimension means infinite
	Box(float width = 1, float length = 1, float height = 1) : dimensions(width / 2, length / 2, height / 2), 
		normalColor({ 1, 1, 1 }), shininess(0), specularColor({ 1, 1, 1 }), reflectivity(0) {};

	//TODO
	double intersects(Ray ray) { return -1; }

	double sdf(const Point& p);

	Color& getColor() {
		return normalColor;
	}

	Color& getSpecularColor() {
		return specularColor;
	}

	float getShininess() {
		return shininess;
	}

	//TODO
	Vector getNormal(const Point& touched) {
		return { 0, 0, 0 };
	}

	float getReflectivity() {
		return reflectivity;
	}
};