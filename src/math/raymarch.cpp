#include "math/raymarch.h"
#include "math/Point.h"
#include "Constants.h"
#include <vector>
#include <memory>

//Returns the shortest distance to an object in the scene with the point and object pointer
raymarch::Hit raymarch::sceneSdf(const Point& p, const std::vector<std::unique_ptr<Object>>& objects) {
	raymarch::Hit ret = {nullptr, p, constants::MARCH_MISS_THRESHOLD + 1};
	for (auto& o : objects) {
		double d = o->sdf(p);
		if (d < ret.dist) ret = {o.get(), p, d};
	}
	return ret;
}

raymarch::Hit raymarch::getNearestHit(const Ray& ray, const std::vector<std::unique_ptr<Object>>& objects) {
	Point moving = ray.P;
	auto closest = raymarch::sceneSdf(moving, objects);
	for (int i = 0; i < constants::MARCH_ITER_LIMIT && closest.dist < constants::MARCH_MISS_THRESHOLD; i++) {
		if (closest.dist < constants::MARCH_HIT_THRESHOLD) {
			return closest;
		}
		moving = moving + (ray.D * closest.dist);
		closest = raymarch::sceneSdf(moving, objects);
	}

	return { nullptr, {}, 0 };
}