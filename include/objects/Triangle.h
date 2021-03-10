#pragma once
#include "objects/Object.h"
#include "math/math.h"

class Triangle : public Object {
	Point p0;
	Point p1;
	Point p2;

	Vector n;
	double k;

	Vector e0;
	Vector e1;
	Vector e2;

	Color normalColor;
	Color specularColor;
	float shininess;
	float reflectivity;

public:
	Triangle(Point p0, Point p1, Point p2, Color normalColor = { 0.478, 0, 1 }, float shininess = 0, Color specularColor = { 1, 1, 1 }, float reflectivity = 0)
		: p0(p0), p1(p1), p2(p2), e0(p1 - p0), e1(p2 - p1), e2(p0 - p2), normalColor(normalColor), shininess(shininess), specularColor(specularColor), reflectivity(reflectivity){
		n = e0.cross(e1).normalize();
		k = n.dot(p0);
	}

	//Uses the given formula to see when a ray intersects the plane, and then if that point is inside the triangle
	double intersects(Ray ray) {
		double denom = ray.D.dot(n);

		//Doesn't count as a hit if it's the back
		if (denom > -0.001) return -1;

		double t = ((k - n.dot(ray.P)) / ray.D.dot(n));

		Point R = ray.P + (ray.D * t);
		
		if (e0.cross(R - p0).dot(n) > -0.001 && e1.cross(R - p1).dot(n) > -0.001 && e2.cross(R - p2).dot(n) > -0.001) return t;
	}

	//NEW
	//TODO make this actually result in a triangle instead of whatever it currently is
	//Returns the shortest distance from the point to the triangle, more or less taken from https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
	double sdf(const Point& p) {
		Vector pa = p - p0;
		Vector pb = p - p1;
		Vector pc = p - p2;
		Vector nor = e0.cross(e2);

		return std::sqrt(
			(math::sign(e0.cross(nor).dot(pa)) +
			math::sign(e1.cross(nor).dot(pb)) +
			math::sign(e2.cross(nor).dot(pc)) < 2.0)
			?
			std::min(std::min(
				(e0 * math::clamp(e0.dot(pa) / e0.magnitudeSquared(), 0.0, 1.0) - pa).magnitudeSquared(),
				(e1 * math::clamp(e1.dot(pb) / e1.magnitudeSquared(), 0.0, 1.0) - pb).magnitudeSquared()),
				(e2 * math::clamp(e2.dot(pc) / e2.magnitudeSquared(), 0.0, 1.0) - pc).magnitudeSquared())
			:
			nor.dot(pa) * nor.dot(pa) / nor.magnitudeSquared());
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