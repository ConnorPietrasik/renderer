#pragma once

#include "objects/Object.h"
#include "math/Matrix.h"
#include <memory>
#include <list>
#include "ofMatrix4x4.h"

#include <iostream>

class TransformedObject : public Object {
	std::shared_ptr<Object> obj;

	//Gave up on own matrix for now, this is 40x faster
	ofMatrix4x4 transform;
	ofMatrix4x4 inverse;

	//Set to false when inverse needs to be updated, to avoid having to update for every transformation
	bool isInverseGood;

	//Keeping record to invert transformations, maybe TEMP, seems easiest though so maybe not
	struct transformation {
		char type;
		float x;
		float y;
		float z;
	};

	std::list<transformation> history;

	void updateInverse();

public:
	TransformedObject(Object* obj) : obj(obj), isInverseGood(true) {}

	void scale(float x, float y, float z) { 
		transform *= ofMatrix4x4::newScaleMatrix(x, y, z);
		history.push_back({ 's', x, y, z });
		isInverseGood = false;
	}

	void translate(float x, float y, float z) {
		transform *= ofMatrix4x4::newTranslationMatrix(x, y, z);
		history.push_back({ 't', x, y, z });
		isInverseGood = false;
	}

	double intersects(Ray ray) { return obj->intersects(ray); }

	double sdf(const Point& p) {
		if (!isInverseGood) updateInverse();
		ofVec3f temp =  ofVec3f(p.x, p.y, p.z) * inverse;
		Point tp(temp.x, temp.y, temp.z);
		double ret = obj->sdf(tp);
		return ret;
	}

	Color& getColor() { return obj->getColor(); }
	Color& getSpecularColor() { return obj->getSpecularColor(); }
	float getShininess() { return obj->getShininess(); }
	float getReflectivity() { return obj->getReflectivity(); }

	Vector getNormal(const Point& touched) { return obj->getNormal(touched); }
};