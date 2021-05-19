#include "objects/SubtractObject.h"

double SubtractObject::sdf(const Point& p) {
	float max = -100000;
	for (auto& sub : subtractors) {
		float tmp = math::max(math::abs(main->sdf(p)), -math::abs(sub->sdf(p)));
		if (tmp > max) max = tmp;
	}

	return max;
}