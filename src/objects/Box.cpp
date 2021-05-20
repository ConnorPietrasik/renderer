#include "objects/Box.h"
#include <limits>

double Box::sdf(const Point& p) {	//More or less taken from https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
	Vector temp = { math::abs(p.x), math::abs(p.y), math::abs(p.z) };
	float x = (dimensions.x < 0) ? 0.0 : math::max(temp.x - dimensions.x, 0.0);
	float y = (dimensions.y < 0) ? 0.0 : math::max(temp.y - dimensions.y, 0.0);
	float z = (dimensions.z < 0) ? 0.0 : math::max(temp.z - dimensions.z, 0.0);
	Vector q{ x, y, z };
	x = (dimensions.x < 0) ? std::numeric_limits<float>::lowest() : temp.x - dimensions.x;
	y = (dimensions.y < 0) ? std::numeric_limits<float>::lowest() : temp.y - dimensions.y;
	z = (dimensions.z < 0) ? std::numeric_limits<float>::lowest() : temp.z - dimensions.z;
	return q.magnitude() + math::min(math::max(math::max(x, y), z), 0.0f);
}