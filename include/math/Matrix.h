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
	Matrix(const std::vector<std::vector<double>>& vals) : vals(vals), m(vals.size()), n(vals[0].size()) {}

	Matrix operator* (const Matrix& x);

	Matrix& operator*= (const Matrix& x);

	friend std::ostream& operator<< (std::ostream& out, const Matrix& m);
};