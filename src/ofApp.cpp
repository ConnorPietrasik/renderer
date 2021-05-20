#include "ofApp.h"
#include "math/raytrace.h"
#include "objects/Sphere.h"
#include "objects/Triangle.h"
#include "math/math.h"
#include "math/raymarch.h"
#include "shaders/Phong.h"
#include "objects/Plane.h"
#include "objects/Torus.h"
#include "objects/Box.h"
#include "objects/NoisyPlane.h"
#include "objects/TransformedObject.h"
#include "objects/RecursiveTetrahedron.h"
#include "objects/SubtractObject.h"
#include "objects/UnionObject.h"
#include "objects/IntersectObject.h"
#include "objects/MengerSponge.h"
#include "Scene.h"
#include "math/Matrix.h"


//--------------------------------------------------------------
void ofApp::setup() {

	//ofMatrix4x4 transform;
	//transform *= ofMatrix4x4::newTranslationMatrix(0, 1, 0);
	//auto inverse = transform.getInverse();

	//ofVec3f point(0, 0, 0);

	//std::cout << "Pre: " << point * inverse << '\n';
	//std::cout << "Post: " << inverse * point << '\n';



	//Matrix x = Matrix::identity();
	//Point p = Point(5, 5, 5);

	//ofMatrix4x4 x2;
	//ofVec3f p2(5, 5, 5);

	//std::chrono::steady_clock::time_point beginTEST = std::chrono::steady_clock::now();

	//auto result = x * p;

	//std::chrono::steady_clock::time_point endTEST = std::chrono::steady_clock::now();
	//std::cout << "Test complete! Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTEST - beginTEST).count() << "ns\n";

	//Matrix x;
	//x.test();
	//TEST
	//Scene::addObject(new NoisyPlane({ 0, 1, 1}, -50, 2, 0.01, 200));

	//Set the shadow function for the Phong shader
	Phong::setShadowedFunc(constants::RENDER_MODE == 0 ? raytrace::isShadowed : raymarch::isShadowed);

	//Set the camera position
	Scene::setCamPos({ 0, 5, 350 });
	//Scene::setCamPos({ 0, 5, 50 });

	auto temp = new TransformedObject(new MengerSponge(300));
	//temp->rotate(45, 1, 1, 0);
	//temp->rotateY(20);
	Scene::addObject(temp);

	//auto temp = new TransformedObject(new Sphere({0, 0, 0}, 1));
	//auto temp = new TransformedObject(new RecursiveTetrahedron(4));
	//auto temp = new TransformedObject(new Box(200, 200, 200));
	//temp->scale(2, 2, 2);
	//temp->translate(0, 400, 0);
	//Scene::addObject(temp);

	//std::list<std::shared_ptr<Object>> l;
	//l.push_back(std::shared_ptr<Object>(new Box(100, 100, 600)));
	//auto temp = new TransformedObject(new SubtractObject(new Box(200, 200, 200), l));
	//temp->translate(0, 400, 0);
	//Scene::addObject(temp);

	//std::list<std::shared_ptr<Object>> ul;
	//ul.push_back(std::shared_ptr<Object>(new Sphere({ 0, 300, 0 }, 100)));
	//ul.push_back(std::shared_ptr<Object>(new Box(200, 200, 200)));
	//Scene::addObject(new UnionObject(ul));

	//std::list<std::shared_ptr<Object>> il;
	//il.push_back(std::shared_ptr<Object>(new Sphere({100, 100, 100}, 100)));
	//il.push_back(std::shared_ptr<Object>(new Box(200, 200, 200)));
	//Scene::addObject(new IntersectObject(il));


	//Adding some spheres: (center, radius, normal_color, shininess, shiny_color, reflectivity)
	//Scene::addObject(new Sphere({ 0, 0, 0 }, 50, { 1, 1, 1 }, 5));
	//Scene::addObject(new Sphere({ 0, 90, 0 }, 40, { 1, 1, 1 }));
	//Scene::addObject(new Sphere({ 0, 160, 0 }, 30, { 1, 1, 1 }));

	//Adding some triangles: (p0, p1, p2, normal_color, shininess, shiny_color, reflectivity)
	//Scene::addObject(new Triangle({ -100, 0, -150 }, { 0, 90, 0 }, { -100, 200, -50 }, { 1, 1, 1 }, 1));
	//Scene::addObject(new Triangle({ 100, 200, -50 }, { 0, 90, 0 }, { 100, 0, -150 }, { 1, 1, 1 }, 1));

	//Adding some lights: (pos, ambient, diffuse, specular, radius)
	//Scene::addLight(new Light({ {-200, 0, 100}, {0.05, 0, 0}, {1, 0, 0}, {0.8, 0, 0}, 20 }));
	//Scene::addLight(new Light({ {200, 0, 100}, {0, 0, 0.05}, {0, 0, 1}, {0, 0, 0.8}, 20 }));
	//Scene::addLight(new Light({ {0, 0, 100}, {0, 0.05, 0}, {0, 1, 0}, {0, 0.8, 0}, 20 }));

	//TEST
	//Scene::addObject(new Torus());
	Scene::addLight(new Light({ {0, 10, 350}, {0.05, 0, 0}, {0.5, 0, 0.7}, {0.8, 0, 0}, 20 }));
	//Scene::addLight(new Light({ {100, 100, 350}, {0.05, 0, 0}, {0.5, 0, 0.7}, {0.8, 0, 0}, 20 }));
	//Scene::addObject(new Plane({ 0, 1, 1 }, 50));
	//Scene::addObject(new Sphere({-400, 0, -600}, 400));
	//Scene::addObject(new Box());

	//Walls
	float wallReflectivity = 0;
	//Scene::addObject(new Triangle({ 100, -500, -500 }, { 100, -500, 500}, { 100, 500, 500}, { 1, 1, 1}, 0, { 0, 0, 0 }, wallReflectivity));
	//Scene::addObject(new Triangle({ 100, 500, 500 }, { 100, 500, -500 }, {100, -500, -500}, { 1, 1, 1 }, 0, { 0, 0, 0 }, wallReflectivity));
	//Scene::addObject(new Triangle({ -100, 500, 500 }, { -100, -500, 500 }, { -100, -500, -500 }, { 1, 1, 1 }, 0, { 0, 0, 0 }, wallReflectivity));
	//Scene::addObject(new Triangle({ -100, -500, -500 }, { -100, 500, -500 },  { -100, 500, 500 }, { 1, 1, 1 }, 0, { 0, 0, 0 }, wallReflectivity));
	//Scene::addObject(new Triangle({ -100, -500, -500 }, { 100, -500, -500 }, { 100, 500, -500 }, { 1, 1, 1 }, 0, { 0, 0, 0 }, wallReflectivity));
	//Scene::addObject(new Triangle({ 100, 500, -500 }, { -100, 500, -500 }, { -100, -500, -500 }, { 1, 1, 1 }, 0, { 0, 0, 0 }, wallReflectivity));

	//Floor
	double floorY = -50;
	float floorReflectivity = 0.25;
	//Scene::addObject(new Triangle({ -500, floorY, -500 }, { -500, floorY, 500 }, { 500, floorY, 500 }, { 1, 1, 1 }, 0, { 0, 0, 0 }, floorReflectivity));
	//Scene::addObject(new Triangle({ 500, floorY, 500 }, { 500, floorY, -500 }, { -500, floorY, -500 }, { 1, 1, 1 }, 0, { 0, 0, 0 }, floorReflectivity));

	//Using all virtual processors for faster draws
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	processorCount = sysinfo.dwNumberOfProcessors;
	//processorCount = 1;

	//Output so the user knows it's running
	std::cout << "Rendering using " << processorCount << " cores...\n";

	//Timing for the first draw
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	std::vector<std::thread> threads;
	for (int i = 0; i < processorCount; i++) {
		threads.emplace_back([this, i] {
			colorRows(i * constants::IMAGE_HEIGHT / processorCount, (i + 1) * constants::IMAGE_HEIGHT / processorCount);
			});
	}

	for (auto& t : threads) {
		t.join();
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Complete! Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms\n";
}

//Uses a mesh to draw the pixel array, more or less copied from example shown
void ofApp::draw(){
	ofMesh m;
	m.setMode(OF_PRIMITIVE_POINTS);

	int n = 0;
	for (int row = 0; row < constants::IMAGE_HEIGHT; row++) {
		for (int col = 0; col < constants::IMAGE_WIDTH; col++) {
			m.addVertex({ col, row, 0 });
			m.addColor({ (float)pixels[row][col].r(), (float)pixels[row][col].g(), (float)pixels[row][col].b() });
			m.addIndex(n++);
		}
	}

	m.draw();
}

//Does the ray tracing for a certain amount of rows to speed things up
void ofApp::colorRows(int start, int end) {

	//Only points in one direction for now, will improve eventually
	Point topLeft = { Scene::getCamPos().x - (constants::IMAGE_WIDTH / 2), Scene::getCamPos().y + (constants::IMAGE_HEIGHT / 2), Scene::getCamPos().z - constants::SCREEN_DISTANCE };

	for (int row = start; row < end; row++) {
		for (int col = 0; col < constants::IMAGE_WIDTH; col++) {
			Color total = { 0, 0, 0 };

			//Splitting the pixel into subpixels for smoother lines, averages the color of each
			for (int subRow = 0; subRow < constants::ANTI_ALIASING_AMOUNT; subRow++) {
				for (int subCol = 0; subCol < constants::ANTI_ALIASING_AMOUNT; subCol++) {
					Point subPixel = { topLeft.x + col + ((double)subCol / constants::ANTI_ALIASING_AMOUNT),
							topLeft.y - row + ((double)subRow / constants::ANTI_ALIASING_AMOUNT), topLeft.z };

					Vector D = subPixel - Scene::getCamPos();
					Ray ray = { Scene::getCamPos(), D.normalize() };


					switch (constants::RENDER_MODE) {
					case 0:

						auto min = raytrace::getNearestHit(ray);

						//If the ray hit something, find the color
						if (min.obj) {
							Point touched = Scene::getCamPos() + D * min.time;
							total += Phong::calculateColor(touched, min.obj, ray);
						}
						break;

					case 1:

						auto hit = raymarch::getNearestHit(ray);
						if (hit.obj) total += Phong::calculateColor(hit.p, hit.obj, ray);

					}
				}
			}
			pixels[row][col] = total / (constants::ANTI_ALIASING_AMOUNT * constants::ANTI_ALIASING_AMOUNT);
		}
	}
}

