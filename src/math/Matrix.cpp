#include "math/Matrix.h"

//Straightforward method, hopefully it'll be good enough
Matrix Matrix::operator*(const Matrix& x) {
	if (n != x.m) throw std::invalid_argument("Left number of columns must equal right number of rows");
	std::vector<std::vector<double>> ret(m, std::vector<double>(x.n, 0));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < x.n; j++) {
			for (int k = 0; k < n; k++) {
				ret[i][j] += vals[i][k] * x.vals[k][j];
			}
		}
	}

	return ret;
}

Matrix& Matrix::operator*=(const Matrix& x) {
	if (n != x.m) throw std::invalid_argument("Left number of columns must equal right number of rows");
	std::vector<std::vector<double>> ret(m, std::vector<double>(x.n, 0));
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

std::ostream& operator<< (std::ostream& out, const Matrix& x) {
	for (int i = 0; i < x.m; i++) {
		for (int j = 0; j < x.n; j++) {
			out << x.vals[i][j] << '\t';
		}
		out << '\n';
	}

	return out;
}