#pragma once

#include "Object.h"
#include "Point.h"
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

}