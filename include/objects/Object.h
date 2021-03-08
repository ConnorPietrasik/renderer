#pragma once
#include "math/Ray.h"
#include "math/Point.h"
#include "Light.h"

class Object {
public:

	//Returns t of intersect
	virtual double intersects(Ray ray) = 0;
	
	//NEW
	//Returns the shortest distance from the point to the object, for use in ray marching
	virtual double sdf(const Point& point) = 0;

	virtual Color& getColor() = 0;
	virtual Color& getSpecularColor() = 0;
	virtual float getShininess() = 0;
	virtual float getReflectivity() = 0;

	virtual Vector getNormal(const Point& touched) = 0;
};