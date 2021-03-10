#pragma once
namespace constants {
	static const int IMAGE_WIDTH = 1200;
	static const int IMAGE_HEIGHT = 1200;
	static const int SCREEN_DISTANCE = 256;			//For a 90deg FOV
	static const int MAX_REFLECTIONS = 20;
	static const int ANTI_ALIASING_AMOUNT = 4;		//Sqrt of the amount of subpixels
	static const int SOFT_SHADOW_AMOUNT = 5;		//Amount of random points on light to sample from
	static const int MAX_DISTANCE = 1000;			//Max distance to render

	//NEW
	static const int RENDER_MODE = 1;				//Render mode, 0 for RT only, 1 for RM only, 2 for mixed. Probably will replace with an enum
	static const int MARCH_MISS_THRESHOLD = 1000;	//Raymarching distance threshold for a miss
	static const double MARCH_HIT_THRESHOLD = 0.05;		//Raymarching distance threshold for a hit
	static const int MARCH_ITER_LIMIT = 200;		//Raymarching iteration limit
}