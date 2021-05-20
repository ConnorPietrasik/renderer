#include "shaders/Phong.h"
#include "math/Point.h"
#include "math/Ray.h"
#include "objects/Object.h"
#include "math/Vector.h"
#include "Constants.h"
#include "math/raymarch.h"
#include "math/raytrace.h"
#include "Scene.h"
#include <vector>
#include <memory>

bool (*Phong::isShadowed)(const Point& point, const Point& lightPoint, Object* obj) = nullptr;

//For soft shadows, checks the portion lit by the light
float Phong::getPortionLit(const Point& point, const Light* light, Object* obj) {
	int litParts = constants::SOFT_SHADOW_AMOUNT;

	for (int i = 0; i < constants::SOFT_SHADOW_AMOUNT; i++) {
		float theta = 2 * 3.1415 * ((float)(std::rand() % 1000) / 1000);		//I know <random> exists, but this is good enough
		float phi = std::acos(2 * ((float)(std::rand() % 1000) / 1000) - 1);	//Seeded in main, fine if it isn't

		Point lPoint = { light->pos.x + light->radius * std::cos(theta) * std::sin(phi),
			light->pos.y + light->radius * std::sin(theta) * std::sin(phi), light->pos.z + light->radius * std::cos(phi) };

		Ray ray = { lPoint, (point - lPoint).normalize() };
		if (isShadowed(point, lPoint, obj)) litParts--;
	}

	return (float)litParts / constants::SOFT_SHADOW_AMOUNT;
}

//Calculates the color of an object at a given point
Color Phong::calculateColor(const Point& pos, Object* obj, const Ray& ray) {

	Color ambient = { 0, 0, 0 };
	Color diffuse = { 0, 0, 0 };
	Color specular = { 0, 0, 0 };

	//Things that don't change with different lights
	//Vector N = obj->getNormal(pos);
	Vector N = raymarch::getNormalRM(pos);
	Vector V = ray.P - pos;
	V.normalize();

	for (auto& light : Scene::getLights()) {
		//Ambient = cMat * cLight
		ambient += obj->getColor() * light->ambient;

		//Diffuse = cMat * cLight * N.L
		Vector L = light->pos - pos;
		L.normalize();

		//So that it doesn't do negative colors if the light is in the other direction
		if (N.dot(L) > 0) {

			if (constants::SOFT_SHADOW_AMOUNT == 1) {
				if (isShadowed == nullptr || !isShadowed(pos, light->pos, obj)) {

					diffuse += obj->getColor() * light->diffuse * N.dot(L);

					//Specular = cMat * cLight * (N.H)^S
					if (obj->getShininess() != 0) {
						Vector H = (V + L).normalize();
						specular += obj->getSpecularColor() * light->specular * math::pow(N.dot(H), obj->getShininess());
					}
				}
			}
			else {
				float shadeCorrection = getPortionLit(pos, light.get(), obj);

				diffuse += obj->getColor() * light->diffuse * N.dot(L) * shadeCorrection;

				//Specular = cMat * cLight * (N.H)^S
				if (obj->getShininess() != 0) {
					Vector H = (V + L).normalize();
					specular += obj->getSpecularColor() * light->specular * math::pow(N.dot(H), obj->getShininess()) * shadeCorrection;
				}
			}
		}
	}

	Color total = ambient + diffuse + specular;

	//if (obj->getReflectivity() > 0) {

	//	Color refColor = { 0, 0, 0 };

	//	if (reflectionCount > constants::MAX_REFLECTIONS) refColor = { 0.4, 0.4, 0.4 };
	//	else {

	//		//Reflected D = -V + 2N(V.N) normalized
	//		Ray refRay = { pos, (-V + (N * 2) * V.dot(N)).normalize() };
	//		Hit refMin = getNearestHit(refRay, objects);

	//		if (refMin.obj) {

	//			Point touched = pos + refRay.D * refMin.time;
	//			refColor = calculateColor(touched, refMin.obj, refRay, lights, objects, reflectionCount + 1);
	//		}
	//	}

	//	total = refColor * obj->getReflectivity() + total * (1 - obj->getReflectivity());
	//}

	if (total.r() > 1) total.r() = 1;
	if (total.g() > 1) total.g() = 1;
	if (total.b() > 1) total.b() = 1;

	return total;
}