#pragma once

#include "objects/Object.h"
#include "math/math.h"

class Box : public Object {
	Point dimensions;

	Color normalColor;
	Color specularColor;
	float shininess;
	float reflectivity;

public:
	Box(float width = 10, float length = 10, float height = 10, Color normalColor = { 1, 1, 1 }, float shininess = 0, Color specularColor = { 1, 1, 1 }, float reflectivity = 0) :
		dimensions(width / 2, length / 2, height / 2), normalColor(normalColor), shininess(shininess), specularColor(specularColor), reflectivity(reflectivity) {};

	//TODO
	double intersects(Ray ray) { return -1; }

	//TODO, doesn't do anything
	double sdf(const Point& p) {	//More or less taken from https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
		Vector temp = { math::abs(p.x), math::abs(p.y), math::abs(p.z) };
		Vector q{ math::max(temp.x - dimensions.x, 0.0), math::max(temp.y - dimensions.y, 0.0), math::max(temp.z - dimensions.z, 0.0) };
		return q.magnitude();
	}

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