#pragma once
#include <iostream>

//Only 4x4 because that's all that will be used in this for now, no need to overcomplicate
class Matrix {
	double M[4][4];

public:
	Matrix() : M() {
		M;
	}

	void test() {
		std::cout << "TEST";
	}
};