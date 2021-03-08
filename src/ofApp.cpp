#include "ofApp.h"
#include "raytrace.h"
#include "Sphere.h"
#include "Triangle.h"
#include "math.h"
#include "raymarch.h"
#include "Phong.h"
#include "Plane.h"
#include "Torus.h"
#include "Box.h"


//--------------------------------------------------------------
void ofApp::setup(){

	//Initialize to black TEST
	for (auto& row : pixels) {
		for (auto& p : row) {
			p = { 0, 0, 0 };
		}
	}

	camera = { 0, 0, 350 };

	//Adding some spheres: (center, radius, normal_color, shininess, shiny_color, reflectivity)
	objects.emplace_back(new Sphere({ 0, 0, 0 }, 50, { 1, 1, 1 }, 5));
	objects.emplace_back(new Sphere({ 0, 90, 0 }, 40, { 1, 1, 1 }));
	objects.emplace_back(new Sphere({ 0, 160, 0 }, 30, { 1, 1, 1 }));

	//Adding some triangles: (p0, p1, p2, normal_color, shininess, shiny_color, reflectivity)
	//objects.emplace_back(new Triangle({ -100, 0, -150 }, { 0, 90, 0 }, { -100, 200, -50 }, { 1, 1, 1 }, 1));
	//objects.emplace_back(new Triangle({ 100, 200, -50 }, { 0, 90, 0 }, { 100, 0, -150 }, { 1, 1, 1 }, 1));

	//Adding some lights: (pos, ambient, diffuse, specular, radius)
	//lights.emplace_back(new Light({ {-200, 0, 100}, {0.05, 0, 0}, {1, 0, 0}, {0.8, 0, 0}, 20 }));
	//lights.emplace_back(new Light({ {200, 0, 100}, {0, 0, 0.05}, {0, 0, 1}, {0, 0, 0.8}, 20 }));
	//lights.emplace_back(new Light({ {0, 0, 100}, {0, 0.05, 0}, {0, 1, 0}, {0, 0.8, 0}, 20 }));

	//TEST	/	NEW
	objects.emplace_back(new Torus());
	lights.emplace_back(new Light({ {0, 0, 350}, {0.05, 0, 0}, {0.5, 0, 0.7}, {0.8, 0, 0}, 20 }));
	objects.emplace_back(new Plane({ 0, 1, 1 }, 50));
	//objects.emplace_back(new Box());

	//Walls
	float wallReflectivity = 0;
	//objects.emplace_back(new Triangle({ 100, -500, -500 }, { 100, -500, 500}, { 100, 500, 500}, { 1, 1, 1}, 0, { 0, 0, 0 }, wallReflectivity));
	//objects.emplace_back(new Triangle({ 100, 500, 500 }, { 100, 500, -500 }, {100, -500, -500}, { 1, 1, 1 }, 0, { 0, 0, 0 }, wallReflectivity));
	//objects.emplace_back(new Triangle({ -100, 500, 500 }, { -100, -500, 500 }, { -100, -500, -500 }, { 1, 1, 1 }, 0, { 0, 0, 0 }, wallReflectivity));
	//objects.emplace_back(new Triangle({ -100, -500, -500 }, { -100, 500, -500 },  { -100, 500, 500 }, { 1, 1, 1 }, 0, { 0, 0, 0 }, wallReflectivity));
	//objects.emplace_back(new Triangle({ -100, -500, -500 }, { 100, -500, -500 }, { 100, 500, -500 }, { 1, 1, 1 }, 0, { 0, 0, 0 }, wallReflectivity));
	//objects.emplace_back(new Triangle({ 100, 500, -500 }, { -100, 500, -500 }, { -100, -500, -500 }, { 1, 1, 1 }, 0, { 0, 0, 0 }, wallReflectivity));

	//Floor
	double floorY = -50;
	float floorReflectivity = 0.25;
	//objects.emplace_back(new Triangle({ -500, floorY, -500 }, { -500, floorY, 500 }, { 500, floorY, 500 }, { 1, 1, 1 }, 0, { 0, 0, 0 }, floorReflectivity));
	//objects.emplace_back(new Triangle({ 500, floorY, 500 }, { 500, floorY, -500 }, { -500, floorY, -500 }, { 1, 1, 1 }, 0, { 0, 0, 0 }, floorReflectivity));

	//Using all virtual processors for faster draws
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	processorCount = sysinfo.dwNumberOfProcessors;

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
	Point topLeft = { camera.x - (constants::IMAGE_WIDTH / 2), camera.y + (constants::IMAGE_HEIGHT / 2), camera.z - constants::SCREEN_DISTANCE };

	for (int row = start; row < end; row++) {
		for (int col = 0; col < constants::IMAGE_WIDTH; col++) {
			Color total = { 0, 0, 0 };

			//Splitting the pixel into subpixels for smoother lines, averages the color of each
			for (int subRow = 0; subRow < constants::ANTI_ALIASING_AMOUNT; subRow++) {
				for (int subCol = 0; subCol < constants::ANTI_ALIASING_AMOUNT; subCol++) {
					Point subPixel = { topLeft.x + col + ((double)subCol / constants::ANTI_ALIASING_AMOUNT),
							topLeft.y - row + ((double)subRow / constants::ANTI_ALIASING_AMOUNT), topLeft.z };

					Vector D = subPixel - camera;
					Ray ray = { camera, D.normalize() };


					switch (constants::RENDER_MODE) {
					case 0:

						auto min = raytrace::getNearestHit(ray, objects);

						//If the ray hit something, find the color
						if (min.obj) {
							Point touched = camera + D * min.time;
							total += Phong::calculateColor(touched, min.obj, ray, lights, objects);
						}
						break;

					//NEW
					case 1:

						auto hit = raymarch::getNearestHit(ray, objects);
						if (hit.obj) total += Phong::calculateColor(hit.p, hit.obj, ray, lights, objects);

					}
				}
			}
			pixels[row][col] = total / (constants::ANTI_ALIASING_AMOUNT * constants::ANTI_ALIASING_AMOUNT);
		}
	}
}

