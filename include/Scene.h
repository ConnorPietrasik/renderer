#pragma once

#include "objects/Object.h"
#include "Light.h"
#include "math/Point.h"
#include <memory>
#include <vector>

class Scene {
	static std::vector<std::unique_ptr<Object>> objects;
	static std::vector<std::unique_ptr<Light>> lights;
	static Point camera;

public:
	static void addObject(Object* obj);
	static void addLight(Light* light);
	static void setCamera(const Point& pos);

};