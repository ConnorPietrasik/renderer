#pragma once

#include "objects/Object.h"
#include "math/raymarch.h"
#include <memory>
#include <list>

class UnionObject : public Object {
	std::list<std::shared_ptr<Object>> objects;

public:
	UnionObject() {}
	UnionObject(std::list<std::shared_ptr<Object>> objects) : objects(objects) {}

	void setObjects(std::list<std::shared_ptr<Object>>& object_list) { objects = object_list; }

	double intersects(Ray ray) { return objects.front()->intersects(ray); }

	double sdf(const Point& p);

	Color& getColor() { return objects.front()->getColor(); }
	Color& getSpecularColor() { return objects.front()->getSpecularColor(); }
	float getShininess() { return objects.front()->getShininess(); }
	float getReflectivity() { return objects.front()->getReflectivity(); }

	Vector getNormal(const Point& touched) { return raymarch::getNormalRM(touched, this); }
};