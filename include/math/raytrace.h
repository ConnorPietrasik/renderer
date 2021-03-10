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
	bool isShadowed(const Point& point, const Point& lightPoint, Object* obj);
	float getPortionLit(const Point& point, const Light* light, Object* obj);
}

