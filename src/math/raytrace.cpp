#include "math/raytrace.h"
#include "objects/Object.h"
#include "math/Ray.h"
#include "Constants.h"
#include "Scene.h"
#include <vector>
#include <memory>
#include <cmath>
#include <cstdlib>

//Returns the nearest object hit with the time
raytrace::Hit raytrace::getNearestHit(const Ray& ray) {
	Hit min = { nullptr, constants::MAX_DISTANCE };
	for (auto& o : Scene::getObjects()) {
		double t = o->intersects(ray);
		if (t > 0 && t < min.time) {
			min = { o.get(), t };
		}
	}
	return min;
}

//Returns true if there is an object between the point and the light that isn't the object itself
bool raytrace::isShadowed(const Point& point, const Point& lightPoint, Object* obj) {
	Ray ray = { lightPoint, (point - lightPoint).normalize() };
	double objT = obj->intersects(ray);

	for (auto& o : Scene::getObjects()) {
		if (o.get() != obj) {
			double t = o->intersects(ray);
			if (t > 0 && t < objT) {
				return true;
			}
		}
	}					
	return false;
}

//Returns a float between 0 and 1 for the amount of light not being blocked (for soft shadows)
float raytrace::getPortionLit(const Point& point, const Light* light, Object* obj) {
	int litParts = constants::SOFT_SHADOW_AMOUNT;

	for (int i = 0; i < constants::SOFT_SHADOW_AMOUNT; i++) {
		float theta = 2 * 3.1415 * ((float)(std::rand() % 1000) / 1000);		//I know <random> exists, but this is good enough
		float phi = std::acos(2 * ((float)(std::rand() % 1000) / 1000) - 1);	//Seeded in main, fine if it isn't

		Point lPoint = { light->pos.x + light->radius * std::cos(theta) * std::sin(phi), 
			light->pos.y + light->radius * std::sin(theta) * std::sin(phi), light->pos.z + light->radius * std::cos(phi) };

		Ray ray = { lPoint, (point - lPoint).normalize() };
		double objT = obj->intersects(ray);
		for (auto& o : Scene::getObjects()) {
			if (o.get() != obj) {
				double t = o->intersects(ray);
				if (t > 0 && t < objT) {
					--litParts;
					break;
				}
			}
		}
	}

	return (float)litParts / constants::SOFT_SHADOW_AMOUNT;
}
