#pragma once
#include "Point.h"
#include "Object.h"
#include "Ray.h"
#include <vector>
#include <memory>

//NEW
class Phong {
public:
	static Color calculateColor(const Point& pos, Object* obj, const Ray& ray, const std::vector<std::unique_ptr<Light>>& lights,
		const std::vector<std::unique_ptr<Object>>& objects);
};