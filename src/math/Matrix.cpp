#include "math/Matrix.h"

//Straightforward method, hopefully it'll be good enough
Matrix Matrix::operator*(const Matrix& x) {
	if (n != x.m) throw std::invalid_argument("Left number of columns must equal right number of rows");
	std::vector<std::vector<double>> ret(m, std::vector<double>(x.n));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < x.n; j++) {
			for (int k = 0; k < n; k++) {
				ret[i][j] = vals[i][k] * vals[k][j];
			}
		}
	}
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