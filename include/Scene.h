#pragma once

#include "objects/Object.h"
#include "Light.h"
#include "math/Point.h"
#include "Camera.h"
#include <memory>
#include <vector>

//This is a static class to avoid having to pass the objects everywhere, probably not the best design... TODO: think about this
class Scene {
	static std::vector<std::unique_ptr<Object>> objects;
	static std::vector<std::unique_ptr<Light>> lights;
	static Camera cam;

public:
	

	static void addObject(Object* obj) { objects.emplace_back(obj); }
	static const std::vector<std::unique_ptr<Object>>& getObjects() { return objects; }

	static void addLight(Light* light) { lights.emplace_back(light); }
	static const std::vector<std::unique_ptr<Light>>& getLights() { return lights; }

	static void setCamera(const Camera& camera) { cam = camera; }
	static const Camera& getCamera() { return cam; }

	static void setCamPos(const Point& pos) { cam.setPos(pos); }
	static const Point& getCamPos() { return cam.getPos(); }

};