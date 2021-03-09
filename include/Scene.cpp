#include "Scene.h"

std::vector<std::unique_ptr<Object>> Scene::objects;
std::vector<std::unique_ptr<Light>> Scene::lights;
Camera Scene::cam;