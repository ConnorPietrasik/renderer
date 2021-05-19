#pragma once

#include "objects/Object.h"
#include <memory>
#include <list>

class SubtractObject : public Object {
	std::shared_ptr<Object> main;
	std::list<std::shared_ptr<Object>> subtractors;

public:
	SubtractObject(Object* main, std::list<std::shared_ptr<Object>> subtractors) : main(main), subtractors(subtractors) {}

	double intersects(Ray ray) { return main->intersects(ray); }

	double sdf(const Point& p);

	Color& getColor() { return main->getColor(); }
	Color& getSpecularColor() { return main->getSpecularColor(); }
	float getShininess() { return main->getShininess(); }
	float getReflectivity() { return main->getReflectivity(); }

	Vector getNormal(const Point& touched) { return main->getNormal(touched); }
};