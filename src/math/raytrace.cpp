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
bool raytrace::isShadowed(const Point& point, const Light* light, Object* obj) {
	Ray ray = { light->pos, (point - light->pos).normalize() };
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

//Calculates the color of an object at a given point
Color raytrace::calculateColor(const Point& pos, Object* obj, const Ray& ray, int reflectionCount) {

	Color ambient = { 0, 0, 0 };
	Color diffuse = { 0, 0, 0 };
	Color specular = { 0, 0, 0 };

	//Things that don't change with different light
	Vector N = obj->getNormal(pos);
	Vector V = ray.P - pos;
	V.normalize();

	for (auto& light : Scene::getLights()) {
		//Ambient = cMat * cLight
		ambient += obj->getColor() * light->ambient;

		//Diffuse = cMat * cLight * N.L
		Vector L = light->pos - pos;
		L.normalize();

		double nDotL = N.dot(L);

		//So that it doesn't do negative colors if the light is in the other direction
		if (nDotL > -0.001) {

			if (constants::SOFT_SHADOW_AMOUNT == 1) {
				if (!isShadowed(pos, light.get(), obj)) {

					diffuse += obj->getColor() * light->diffuse * N.dot(L);

					//Specular = cMat * cLight * (N.H)^S
					if (obj->getShininess() != 0) {
						Vector H = (V + L).normalize();
						specular += obj->getSpecularColor() * light->specular * math::pow(N.dot(H), obj->getShininess());
					}
				}
			}
			else {
				float shadowCorrect = getPortionLit(pos, light.get(), obj);

				diffuse += obj->getColor() * light->diffuse * N.dot(L) * shadowCorrect;

				//Specular = cMat * cLight * (N.H)^S
				if (obj->getShininess() != 0) {
					Vector H = (V + L).normalize();
					specular += obj->getSpecularColor() * light->specular * math::pow(N.dot(H), obj->getShininess()) * shadowCorrect;
				}
			}
		}
	}

	Color total = ambient + diffuse + specular;

	if (obj->getReflectivity() > 0) {

		Color refColor = { 0, 0, 0 };

		if (reflectionCount > constants::MAX_REFLECTIONS) refColor = { 0.4, 0.4, 0.4 };
		else {

			//Reflected D = -V + 2N(V.N) normalized
			Ray refRay = { pos, (-V + (N * 2) * V.dot(N)).normalize() };
			Hit refMin = getNearestHit(refRay);

			if (refMin.obj) {

				Point touched = pos + refRay.D * refMin.time;
				refColor = calculateColor(touched, refMin.obj, refRay, reflectionCount + 1);
			}
		}

		total = refColor * obj->getReflectivity() + total * (1 - obj->getReflectivity());
	}

	if (total.r() > 1) total.r() = 1;
	if (total.g() > 1) total.g() = 1;
	if (total.b() > 1) total.b() = 1;

	return total;
}