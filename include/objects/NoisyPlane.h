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

		//TODO: Replace GLM perlin with own implementation or something
		double noise = amplitude * glm::perlin(glm::vec3(frequency * p.x, frequency * p.y, frequency * p.z));

		//I assumed I was allowed to use glm::perlin because you said we could use it for our work in the March 2nd lecture at 1:04:06
		for (int i = 1; i < octaves; i++) {
			noise += (amplitude / (2 * i)) * perlin(glm::vec3(2 * i * frequency * p.x, 2 * i * frequency * p.y, 2 * i * frequency * p.z));
		}
		return n.dot(p) + h + noise;
	}
};