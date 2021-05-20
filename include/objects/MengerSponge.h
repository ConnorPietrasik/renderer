#pragma once
#include "objects/Object.h"
#include "objects/Box.h"
#include "objects/UnionObject.h"
#include <memory>
#include <list>

#include "objects/Sphere.h"

class MengerSponge : public Object {
	Box box;
	float size;
	int iterations;
	UnionObject cross;

public:
	MengerSponge(float size = 200, int iterations = 4);

	double intersects(Ray ray) { return box.intersects(ray); }

	double sdf(const Point& p);

	Color& getColor() { return box.getColor(); }
	Color& getSpecularColor() { return box.getSpecularColor(); }
	float getShininess() { return box.getShininess(); }
	float getReflectivity() { return box.getReflectivity(); }

	Vector getNormal(const Point& touched) { return box.getNormal(touched); }
};