#include "math/Point.h"
#include "math/Vector.h"


Point::Point() : x(0), y(0), z(0) {}
Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

double& Point::r() { return x; }
double& Point::g() { return y; }
double& Point::b() { return z; }

Vector Point::operator-(const Point& obj) const {
	return { x - obj.x, y - obj.y, z - obj.z };
}

Point Point::operator+(const Point& obj) const {
	return { x + obj.x, y + obj.y, z + obj.z };
}

Point Point::operator+(const Vector& obj) const {
	return { x + obj.x, y + obj.y, z + obj.z };
}

//Componentwise multiply
Point Point::operator*(const Point& obj) const {
	return { x * obj.x, y * obj.y, z * obj.z };
}

//Scale
Point Point::operator/(double scalar) const {
	return { x / scalar, y / scalar, z / scalar };
}

void Point::operator+=(const Point& obj) {
	x += obj.x;
	y += obj.y;
	z += obj.z;
}

Point::operator Vector() const {
	return { x, y, z };
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
	out << '(' << p.x << ", " << p.y << ", " << p.z << ')';
	return out;
}