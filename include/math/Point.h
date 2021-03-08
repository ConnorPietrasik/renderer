#pragma once
#include <type_traits>
#include <ostream>

struct Vector;

struct Point {
	double x;
	double y;
	double z;

	double& r();
	double& g();
	double& b();

	Point();
	Point(double x, double y, double z);

	Vector operator-(const Point& obj) const;
	Point operator+(const Point& obj) const;
	Point operator+(const Vector& obj) const;

	//Componentwise multiply
	Point operator*(const Point& obj) const;

	template<typename T, typename = std::enable_if<std::is_arithmetic<T>::value>>
	Point operator*(T scalar) const {
		return { scalar * x, scalar * y, scalar * z };
	}

	Point operator/(double scalar) const;

	void operator+=(const Point& obj);

	operator Vector() const;
};

//They're basically the same thing just with a different name, no need to make a new struct
using Color = Point;

std::ostream& operator<<(std::ostream& out, const Point& p);