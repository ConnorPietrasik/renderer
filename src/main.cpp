#include "ofMain.h"
#include "ofApp.h"
#include "Constants.h"
#include <cstdlib>
#include <time.h>

//========================================================================
int main( ){
	std::srand(time(0));

	ofSetupOpenGL(constants::IMAGE_WIDTH, constants::IMAGE_HEIGHT, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
