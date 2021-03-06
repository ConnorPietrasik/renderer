#pragma once
#include "objects/Object.h"
#include "math/Vector.h"

//NEW
class Plane : public Object {
	Color normalColor;
	Color specularColor;
	float shininess;
	float reflectivity;

protected:
	Vector n;
	double h;

public:
	Plane(Vector normal = { 0, 1, 0 }, double height = 0, Color normalColor = {1, 1, 1}, float shininess = 0, Color specularColor = { 1, 1, 1 }, float reflectivity = 0) : 
		n(normal.getNormalized()), h(-height), normalColor(normalColor), shininess(shininess), specularColor(specularColor), reflectivity(reflectivity) {}

	//TODO
	double intersects(Ray ray) { return -1; }

	virtual double sdf(const Point& p) {	//Taken from https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
		return n.dot(p) + h;
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

	Vector getNormal(const Point& touched) {
		return n;
	}

	float getReflectivity() {
		return reflectivity;
	}

};