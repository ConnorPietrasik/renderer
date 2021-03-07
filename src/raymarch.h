#pragma once

#include "Object.h"
#include "Point.h"
#include <vector>
#include <memory>

//NEW
namespace raymarch {
	struct Hit {
		Object* obj;
		Point p;
	};

	double sceneSdf(const Point& p, const std::vector<std::unique_ptr<Object>>& objects);


}