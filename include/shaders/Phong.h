#pragma once
#include "math/Point.h"
#include "objects/Object.h"
#include "math/Ray.h"
#include <vector>
#include <memory>

//NEW
class Phong {
	static bool (*isShadowed)(const Point& point, const Point& lightPoint, Object* obj);
	static float getPortionLit(const Point& point, const Light* light, Object* obj);

public:
	static Color calculateColor(const Point& pos, Object* obj, const Ray& ray);

	static void setShadowedFunc(bool (*isShadowedFunc)(const Point& point, const Point& lightPoint, Object* obj)) { isShadowed = isShadowedFunc; }
};