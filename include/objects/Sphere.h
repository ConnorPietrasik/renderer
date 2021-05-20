#pragma once
#include "objects/Object.h"
#include "math/Vector.h"
#include "math/math.h"
#include "math/Point.h"

class Sphere : public Object {
	Point pos;
	double radius;
	double radiusSquared; //Saving this so it doesn't have to be computed each time
	Color normalColor;
	Color specularColor;
	float shininess;
	float reflectivity;

public:
	Sphere(const Point& center = { 0, 0, 0 }, double radius = 1, Color normalColor = { 0.478, 0, 1 }, float shininess = 0, Color specularColor = { 1, 1, 1 }, float reflectivity = 0)
		: pos(center), radius(radius), radiusSquared(radius* radius), normalColor(normalColor), shininess(shininess), specularColor(specularColor), reflectivity(reflectivity) {}

	//Uses the given formula to find if the ray intersects the sphere, and returns the first time it does
	double intersects(Ray ray) {
		Vector M = ray.P - pos;
		double DDotM = ray.D.dot(M);
		double sqrtpart = math::pow(DDotM, 2) - (M.magnitudeSquared() - radiusSquared);
		if (sqrtpart <= 0) return -1;

		//Only this one since - will always be less, I'm ignoring the possibility of camera being inside sphere
		return -DDotM - std::sqrt(sqrtpart);
	}

	//Returns the distance to the edge of the sphere
	double sdf(const Point& p) {
		double ret = (p - pos).magnitude() - radius;
		return ret;	//Taken from lecture
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
		return ((Vector)(touched - pos)).normalize();
	}

	float getReflectivity() {
		return reflectivity;
	}
};