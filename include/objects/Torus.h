#pragma once

#include "objects/Object.h"

//NEW
class Torus : public Object {

	Point t;	//TODO: I'm not totally sure what each part of this is


	Color normalColor;
	Color specularColor;
	float shininess;
	float reflectivity;

public:
	Torus(Point t = { 75, 25, 75 }, Color normalColor = { 1, 1, 1 }, float shininess = 0, Color specularColor = { 1, 1, 1 }, float reflectivity = 0) :
		t(t), normalColor(normalColor), shininess(shininess), specularColor(specularColor), reflectivity(reflectivity) {};

	//TODO
	double intersects(Ray ray) { return -1; }

	double sdf(const Point& p) {	//More or less taken from https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
		Vector temp = { p.x, 0, p.z };
		Vector q = { temp.magnitude() - t.x, p.y - 200, 0 };	//TODO do transformations
		return q.magnitude() - t.y;
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