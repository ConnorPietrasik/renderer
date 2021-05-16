#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>

//Only 4x4 because that's all that will be used in this for now, no need to overcomplicate
class Matrix {
	std::vector<std::vector<double>> vals;
	int m, n;

public:

	//Default is 4x4 identity
	Matrix() : vals({ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} }), m(4), n(4) {}
	Matrix(const std::vector<std::vector<double>>& vals) : vals(vals), m(vals.size()), n(vals[0].size()) {}

	Matrix operator* (const Matrix& x);

	//Post-multiply, so transformations nearest get done first
	Matrix& operator*= (const Matrix& x);

	friend std::ostream& operator<< (std::ostream& out, const Matrix& m);
};