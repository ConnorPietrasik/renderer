#include "shaders/Phong.h"
#include "math/Point.h"
#include "math/Ray.h"
#include "objects/Object.h"
#include "math/Vector.h"
#include "Constants.h"
#include "math/raymarch.h"
#include <vector>
#include <memory>

//TODO move this where it belongs and such. 
//NEW
//It also makes circles do some weird thing in the middle, but it looks cool so I'll leave it be for now (no time for lengthy debugging)
Vector getNormalRM(const Point& p, const std::vector<std::unique_ptr<Object>>& objects) {	//More or less taken from lecture slide
	double eps = 0.01;
	double dp = raymarch::sceneSdf(p, objects).dist;
	Vector n = { dp - raymarch::sceneSdf({p.x - eps, p.y, p.z}, objects).dist,
				dp - raymarch::sceneSdf({p.x, p.y - eps, p.z}, objects).dist,
				dp - raymarch::sceneSdf({p.x, p.y, p.z - eps}, objects).dist };
	return n.getNormalized();
}

//TODO This belongs in raymarch, should have it choose between them and what not
//NEW
//Returns true if there is an object between the point and the light that isn't the object itself
bool isShadowed(const Point& point, const Light* light, Object* obj, const std::vector<std::unique_ptr<Object>>& objects) {
	Ray ray = { point, (light->pos - point).normalize() };

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

//Calculates the color of an object at a given point
Color Phong::calculateColor(const Point& pos, Object* obj, const Ray& ray, const std::vector<std::unique_ptr<Light>>& lights,
	const std::vector<std::unique_ptr<Object>>& objects) {

	Color ambient = { 0, 0, 0 };
	Color diffuse = { 0, 0, 0 };
	Color specular = { 0, 0, 0 };

	//Things that don't change with different light
	//Vector N = obj->getNormal(pos);
	Vector N = getNormalRM(pos, objects);
	Vector V = ray.P - pos;
	V.normalize();

	for (auto& light : lights) {
		//Ambient = cMat * cLight
		ambient += obj->getColor() * light->ambient;

		//Diffuse = cMat * cLight * N.L
		Vector L = light->pos - pos;
		L.normalize();

		double nDotL = N.dot(L);

		//So that it doesn't do negative colors if the light is in the other direction
		if (nDotL > -0.001) {

			if (constants::SOFT_SHADOW_AMOUNT == 1) {
				if (!isShadowed(pos, light.get(), obj, objects)) {

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