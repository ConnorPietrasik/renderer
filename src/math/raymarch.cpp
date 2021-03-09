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

//Returns the closest object hit by the ray with relevant info
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

//Returns true if there is an object between the point and the light that isn't the object itself
bool raymarch::isShadowed(const Point& point, const Light* light, Object* obj, const std::vector<std::unique_ptr<Object>>& objects) {
	Ray ray = { point, (light->pos - point).getNormalized() };

	Point moving = ray.P;
	auto closest = raymarch::sceneSdf(moving, objects);
	for (int i = 0; i < constants::MARCH_ITER_LIMIT && closest.dist < constants::MARCH_MISS_THRESHOLD; i++) {
		if (closest.dist < constants::MARCH_HIT_THRESHOLD && closest.obj != obj) {
			return true;
		}
		moving = moving + (ray.D * closest.dist);
		closest = raymarch::sceneSdf(moving, objects);
	}

	return false;
}

//Returns the normal at a point using raymarching
Vector raymarch::getNormalRM(const Point& p, const std::vector<std::unique_ptr<Object>>& objects) {	//More or less taken from lecture slide
	double eps = 0.01;
	double dp = raymarch::sceneSdf(p, objects).dist;
	Vector n = { dp - raymarch::sceneSdf({p.x - eps, p.y, p.z}, objects).dist,
				dp - raymarch::sceneSdf({p.x, p.y - eps, p.z}, objects).dist,
				dp - raymarch::sceneSdf({p.x, p.y, p.z - eps}, objects).dist };
	return n.getNormalized();
}