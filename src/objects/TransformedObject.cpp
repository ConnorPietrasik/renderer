#include "objects/TransformedObject.h"

//Leaving this here just in case I come back to it

////Applies the transformations in reverse order
//void TransformedObject::updateInverse() {
//	inverse = Matrix::identity();
//	for (auto i = history.rbegin(); i != history.rend(); ++i) {
//		switch (i->type) {
//		case 's': 
//			inverse *= Matrix::scale(-i->x, -i->y, -i->z);
//		}
//	}
//
//	isInverseGood = true;
//}

//Applies the opposite transformations in reverse order
void TransformedObject::updateInverse() {
	inverse = transform.getInverse();
	isInverseGood = true;
}

double TransformedObject::sdf(const Point& p) {
	if (!isInverseGood) updateInverse();
	ofVec3f temp = ofVec3f(p.x, p.y, p.z) * inverse;
	return obj->sdf(Point(temp.x, temp.y, temp.z));
}