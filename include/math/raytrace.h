#pragma once

#include "objects/Object.h"
#include "math/Ray.h"
#include <vector>
#include <memory>

struct Ray;
struct Light;

namespace raytrace {
	struct Hit {
		Object* obj;
		double time;
	};

	Hit getNearestHit(const Ray& ray);
	bool isShadowed(const Point& point, const Light* light, Object* obj);
	float getPortionLit(const Point& point, const Light* light, Object* obj);

	//Returns the color at a given point, assuming it's on the given object. Needs objects vector for reflections
	Color calculateColor(const Point& pos, Object* obj, const Ray& ray, int reflectionCount = 0);
}

