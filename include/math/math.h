#pragma once
#include <type_traits>

namespace math {
	//Returns x^n
	double pow(double x, int n);

	//NEW
	//Returns X if it's between min and max, otherwise returns min or max
	template <typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, T>::type clamp(T x, T min, T max) {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

	//Returns the sign of the given number (-1, 0, 1)
	template <typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, T>::type sign(T x) {
		double eps = 0.00000001;
		if (x > eps) return 1;
		if (x < -eps) return -1;
		return 0;
	}

	//Returns the absolute value of the given number
	template <typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, T>::type abs(T x) {
		return (x < 0) ? -x : x;
	}

	//Returns the max of given numbers
	template <typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, T>::type max(T a, T b) {
		return (a > b) ? a : b;
	}

	//Returns the min of given numbers
	template <typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, T>::type min(T a, T b) {
		return (a < b) ? a : b;
	}
}

