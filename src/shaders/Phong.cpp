#include "shaders/Phong.h"
#include "math/Point.h"
#include "math/Ray.h"
#include "objects/Object.h"
#include "math/Vector.h"
#include "Constants.h"
#include "math/raymarch.h"
#include <vector>
#include <memory>

//Calculates the color of an object at a given point
Color Phong::calculateColor(const Point& pos, Object* obj, const Ray& ray, const std::vector<std::unique_ptr<Light>>& lights,
	const std::vector<std::unique_ptr<Object>>& objects) {

	Color ambient = { 0, 0, 0 };
	Color diffuse = { 0, 0, 0 };
	Color specular = { 0, 0, 0 };

	//Things that don't change with different light
	//Vector N = obj->getNormal(pos);
	Vector N = raymarch::getNormalRM(pos, objects);
	Vector V = ray.P - pos;
	V.normalize();

	for (auto& light : lights) {
		//Ambient = cMat * cLight
		ambient += obj->getColor() * light->ambient;

		//Diffuse = cMat * cLight * N.L
		Vector L = light->pos - pos;
		L.normalize();

		//So that it doesn't do negative colors if the light is in the other direction
		if (N.dot(L) > 0) {

			if (constants::SOFT_SHADOW_AMOUNT == 1) {
				if (!raymarch::isShadowed(pos, light.get(), obj, objects)) {

					diffuse += obj->getColor() * light->diffuse * N.dot(L);

					//Specular = cMat * cLight * (N.H)^S
					if (obj->getShininess() != 0) {
						Vector H = (V + L).normalize();
						specular += obj->getSpecularColor() * light->specular * math::pow(N.dot(H), obj->getShininess());
					}
				}
			}
			//else {
			//	float shadowCorrect = getPortionLit(pos, light.get(), obj, objects);

			//	diffuse += obj->getColor() * light->diffuse * N.dot(L) * shadowCorrect;

			//	//Specular = cMat * cLight * (N.H)^S
			//	if (obj->getShininess() != 0) {
			//		Vector H = (V + L).normalize();
			//		specular += obj->getSpecularColor() * light->specular * math::pow(N.dot(H), obj->getShininess()) * shadowCorrect;
			//	}
			//}
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