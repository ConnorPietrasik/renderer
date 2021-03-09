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

	Hit sceneSdf(const Point& p, const std::vector<std::unique_ptr<Object>>& objects);

	Hit getNearestHit(const Ray& ray, const std::vector<std::unique_ptr<Object>>& objects);

	bool isShadowed(const Point& point, const Light* light, Object* obj, const std::vector<std::unique_ptr<Object>>& objects);

	Vector getNormalRM(const Point& p, const std::vector<std::unique_ptr<Object>>& objects);
}