#include "objects/MengerSponge.h"
#include "math/math.h"
#include <cmath>

//Sets up the cross, -1 is infinite
MengerSponge::MengerSponge(float size, int iterations) : box(1, 1, 1), size(size), iterations(iterations) {
	std::list<std::shared_ptr<Object>> temp;
	temp.emplace_back(new Box(-1, 1, 1));
	temp.emplace_back(new Box(1, -1, 1));
	temp.emplace_back(new Box(1, 1, -1));
	cross.setObjects(temp);
}

double MengerSponge::sdf(const Point& p) {

	//Takes the absolute value to make it spread to more than just the top right quadrant
	Point np(math::abs(p.x), math::abs(p.y), math::abs(p.z));

	//Scaling it with the final size since working with objects of size 1 is easiest
	np = np / size;

	//Somewhat got these numbers from https://iquilezles.org/www/articles/menger/menger.htm, not exactly though
	double s = 3;
	double c = 2;

	double d = box.sdf(np);
	for (int i = 0; i < iterations; i++) {

		//Infinite repition of the cross
		Point q(std::fmod(np.x + 0.5 * c, c) - 0.5 * c, std::fmod(np.y + 0.5 * c, c) - 0.5 * c, std::fmod(np.z + 0.5 * c, c) - 0.5 * c);

		//Subtraction of the cross from the cube
		d = math::max(d, -cross.sdf(q * s) / s);

		//Shrinking the cross and the repitition period by a factor of 3
		s *= 3;
		c /= 3;
	}
	return d * size;
}