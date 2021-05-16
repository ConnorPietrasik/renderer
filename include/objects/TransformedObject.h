#pragma once

#include "objects/Object.h"
#include "math/Matrix.h"
#include <memory>

class TransformedObject : public Object {
	std::shared_ptr<Object> obj;
	Matrix transform;
	Matrix inverse;

	//Set to true when inverse needs to be updated, to avoid having to update for every transformation
	bool updateInverse;

public:
	TransformedObject(Object* obj) : obj(obj), updateInverse(false) {}

	double intersects(Ray ray) { return obj->intersects(ray); }
	double sdf(const Point& p) { return obj->sdf(p); }

	Color& getColor() { return obj->getColor(); }
	Color& getSpecularColor() { return obj->getSpecularColor(); }
	float getShininess() { return obj->getShininess(); }
	float getReflectivity() { return obj->getReflectivity(); }

	Vector getNormal(const Point& touched) { return obj->getNormal(touched); }
};