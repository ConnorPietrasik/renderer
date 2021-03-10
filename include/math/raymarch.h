#pragma once

#include "objects/Object.h"
#include "Light.h"
#include "math/Point.h"
#include <vector>
#include <memory>

//NEW
namespace raymarch {
	struct Hit {
		Object* obj;
		Point p;
		double dist;
	};

	Hit sceneSdf(const Point& p);

	Hit getNearestHit(const Ray& ray);

	bool isShadowed(const Point& point, const Light* light, Object* obj);

	Vector getNormalRM(const Point& p);
}