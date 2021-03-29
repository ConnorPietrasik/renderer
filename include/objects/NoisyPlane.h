#pragma once

#include "Plane.h"

class NoisyPlane : public Plane {
	int octaves;
	float frequency;
	float amplitude;

public:
	NoisyPlane(Vector normal = { 0, 1, 0 }, double height = 0, int octaves = 1, float frequency = 1.0, float amplitude = 1.0, Color normalColor = { 1, 1, 1 }, float shininess = 0, Color specularColor = { 1, 1, 1 }, float reflectivity = 0) : 
		Plane(normal, height, normalColor, shininess, specularColor, reflectivity), octaves(octaves), frequency(frequency), amplitude(amplitude) {}

	double sdf(const Point& p) {
		return n.dot(p) + h + glm::perlin(glm::vec3(p.x, p.y, p.z), glm::vec3(2.0f));
	}
};