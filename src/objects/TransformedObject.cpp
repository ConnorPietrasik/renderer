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

	/*inverse.makeIdentityMatrix();
	for (auto i = history.rbegin(); i != history.rend(); ++i) {
		switch (i->type) {
		case 's':
			inverse *= ofMatrix4x4::newScaleMatrix(1.0 / i->x, 1.0 / i->y, 1.0 / i->z);
		}
	}*/

	isInverseGood = true;
}