#include "math/Matrix.h"
#include "math/Point.h"
#include <stdexcept>

//Straightforward method, hopefully it'll be good enough
Matrix Matrix::operator*(const Matrix& x) {
	if (n != x.m) throw std::invalid_argument("Left number of columns must equal right number of rows");
	std::vector<std::vector<float>> ret(m, std::vector<float>(x.n, 0));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < x.n; j++) {
			for (int k = 0; k < n; k++) {
				ret[i][j] += vals[i][k] * x.vals[k][j];
			}
		}
	}

	return ret;
}

//Post-multiply
Matrix& Matrix::operator*=(const Matrix& x) {
	if (n != x.m) throw std::invalid_argument("Left number of columns must equal right number of rows");
	std::vector<std::vector<float>> ret(m, std::vector<float>(x.n, 0));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < x.n; j++) {
			for (int k = 0; k < n; k++) {
				ret[i][j] += vals[i][k] * x.vals[k][j];
			}
		}
	}
	vals = ret;
	m = ret.size();
	n = ret[0].size();

	return *this;
}

//Transforms the given point
Point Matrix::operator*(const Point& p) {
	if (n != 4) throw std::domain_error("Matrix must be 4x4 to transform a point");
	
	Matrix temp = *this * Matrix({ {(float)p.x}, {(float)p.y}, {(float)p.z}, {1} }); //TODO: get rid of the casts after changing Point to float
	Point ret(temp[0][0] / temp[3][0], temp[1][0] / temp[3][0], temp[2][0] / temp[3][0]);

	return ret;
}

std::ostream& operator<< (std::ostream& out, const Matrix& x) {
	for (int i = 0; i < x.m; i++) {
		for (int j = 0; j < x.n; j++) {
			out << x.vals[i][j] << '\t';
		}
		out << '\n';
	}

	return out;
}

