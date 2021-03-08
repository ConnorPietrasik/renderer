#include "math/Vector.h"
#include "math/math.h"
#include <cmath>
#include "math/Point.h"

double Vector::dot(const Vector& obj) const {
	return x * obj.x + y * obj.y + z * obj.z;
}

Vector Vector::cross(const Vector& b) const {
	return {y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x};
}

Vector Vector::operator-(const Vector& obj) const {
	return { x - obj.x, y - obj.y, z - obj.z };
}

Vector Vector::operator+(const Vector& obj) const {
	return { x + obj.x, y + obj.y, z + obj.z };
}

//Scaled
Vector Vector::operator*(double scalar) const {
	return { x * scalar, y * scalar, z * scalar };
}

Vector Vector::operator/(double scalar) const {
	return { x / scalar, y / scalar, z / scalar };
}

double Vector::magnitude() const {
	return std::sqrt(math::pow(x, 2) + math::pow(y, 2) + math::pow(z, 2));
}

double Vector::magnitudeSquared() const {
	return math::pow(x, 2) + math::pow(y, 2) + math::pow(z, 2);
}

Vector& Vector::normalize() {
	double mag = magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
	return *this;
}

Vector Vector::getNormalized() const {
	double mag = magnitude();
	return { x / mag, y / mag, z / mag };
}

Vector::operator Point() const {
	return { x, y, z };
}

Vector Vector::operator-() {
	return { -x, -y, -z };
}