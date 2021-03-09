#pragma once
#include "math/Point.h"
#include "objects/Object.h"
#include "math/Ray.h"
#include <vector>
#include <memory>

//NEW
class Phong {

public:
	static Color calculateColor(const Point& pos, Object* obj, const Ray& ray, const std::vector<std::unique_ptr<Light>>& lights,
		const std::vector<std::unique_ptr<Object>>& objects);
};