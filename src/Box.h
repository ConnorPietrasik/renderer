#pragma once

#include "Object.h"
#include "math.h"

class Box : public Object {
	Point b;

	Color normalColor;
	Color specularColor;
	float shininess;
	float reflectivity;

public:
	Box(Point b = { 1000, 1000, 1000 }, Color normalColor = { 1, 1, 1 }, float shininess = 0, Color specularColor = { 1, 1, 1 }, float reflectivity = 0) :
		b(b), normalColor(normalColor), shininess(shininess), specularColor(specularColor), reflectivity(reflectivity) {};

	//TODO
	double intersects(Ray ray) { return -1; }

	//TODO, doesn't do anything
	double sdf(const Point& p) {	//More or less taken from https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
		Vector temp = { math::abs(p.x), math::abs(p.y), math::abs(p.z) };
		Vector q = temp - b;
		return math::max(q.magnitude(), 0.0) + math::min(math::max(q.x, math::max(q.y, q.z)), 0.0);
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