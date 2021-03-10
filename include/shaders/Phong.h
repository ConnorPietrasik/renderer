#pragma once
#include "math/Point.h"
#include "objects/Object.h"
#include "math/Ray.h"
#include <vector>
#include <memory>

//NEW
class Phong {

public:
	static Color calculateColor(const Point& pos, Object* obj, const Ray& ray);
};