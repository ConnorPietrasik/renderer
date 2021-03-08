#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "Point.h"
#include "Object.h"
#include "Light.h"
#include "Ray.h"

class ofApp : public ofBaseApp{
	int processorCount;

	Color pixels[constants::IMAGE_WIDTH][constants::IMAGE_HEIGHT];
	Point camera;
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<std::unique_ptr<Light>> lights;

	//Function so it can be split into multiple threads
	void colorRows(int start, int end);

	void rayTrace() {}

public:
	void setup();
	void update() {}
	void draw();

	void keyPressed(int key) {}
	void keyReleased(int key) {}
	void mouseMoved(int x, int y) {}
	void mouseDragged(int x, int y, int button) {}
	void mousePressed(int x, int y, int button) {}
	void mouseReleased(int x, int y, int button) {}
	void mouseEntered(int x, int y) {}
	void mouseExited(int x, int y) {}
	void windowResized(int w, int h) {}
	void dragEvent(ofDragInfo dragInfo) {}
	void gotMessage(ofMessage msg) {}
		
};
