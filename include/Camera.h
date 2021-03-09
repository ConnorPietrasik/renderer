#pragma once

#include "math/Point.h"
#include "math/Vector.h"

class Camera {
	Point pos;
	Vector dir;

public:
	Camera(Point pos = {}, Vector dir = {}) : pos(pos), dir(dir) {}


	void setPos(const Point& pos) { this->pos = pos; }
	const Point& getPos() { return pos; }

	void setDir(const Vector& dir) { this->dir = dir; }
	const Vector& getDir() { return dir; }
};