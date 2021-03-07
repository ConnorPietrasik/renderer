#include "raymarch.h"
#include "Point.h"
#include "Constants.h"
#include <vector>
#include <memory>

double raymarch::sceneSdf(const Point& p, const std::vector<std::unique_ptr<Object>>& objects) {
	double min = -1;
	for (auto& o : objects) {
		double d = o->sdf(p);
		if (d > min && d < constants::MAX_DISTANCE) min = d;
	}
	return min;
}

