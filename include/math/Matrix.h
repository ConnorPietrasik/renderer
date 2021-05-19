#pragma once
#include "math/Point.h"
#include <vector>
#include <memory>
#include <iostream>

//Only 4x4 because that's all that will be used in this for now, no need to overcomplicate
class Matrix {
	std::vector<std::vector<float>> vals;
	int m, n;

public:

	//Default is 4x4 identity
	Matrix() : vals({ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} }), m(4), n(4) {}
	Matrix(const std::vector<std::vector<float>>& vals) : vals(vals), m(vals.size()), n(vals[0].size()) {}

	Matrix operator* (const Matrix& x);

	//Post-multiply, so transformations nearest get done first
	Matrix& operator*= (const Matrix& x);

	//To transform the given point
	Point operator* (const Point& p);

	std::vector<float>& operator[] (int x) { return vals[x]; }

	friend std::ostream& operator<< (std::ostream& out, const Matrix& m);

	//Standard 4x4 matrices
	static Matrix identity() { return Matrix(); }
	static Matrix scale(float x, float y, float z) { return Matrix({ {x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1} }); }
};