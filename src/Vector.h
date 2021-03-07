#pragma once

#include "math.h"
#include <cmath>

struct Point;

struct Vector {
	double x;
	double y;
	double z;

	double dot(const Vector& obj) const;
	Vector cross(const Vector& b) const;
	double magnitude() const;
	double magnitudeSquared() const;
	Vector& normalize();
	Vector getNormalized() const;

	Vector operator-(const Vector& obj) const;
	Vector operator+(const Vector& obj) const;

	//Scaled
	Vector operator*(double scalar) const;
	Vector operator/(double scalar) const;

	//Negation
	Vector operator-();

	operator Point() const;
};