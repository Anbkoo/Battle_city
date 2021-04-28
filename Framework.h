#pragma once
#include "Map.h"
#include "Component.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>

#if defined(_WINDOWS)

	#if defined(FRAMEWORK_PROJECT)
		#define FRAMEWORK_API extern "C" __declspec(dllexport)
	#else
		#define FRAMEWORK_API extern "C" __declspec(dllimport)
	#endif
#else
	#define FRAMEWORK_API 
#endif

//Tile constants
const int FPS = 60;
const int frameDelay = 1000 / FPS;
//extern Bullet* mBullets[50];

class Framework : public Container_Component {
public:
	// return : true - ok, false - failed, application will exit
	virtual bool Init() = 0;

	virtual int Close() = 0;

	virtual const char* GetTitle() = 0;

	virtual ~Framework() {};

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool running;
	
	enum Groups : std::size_t {
		groupEnemies,
		groupPlayers
	};

};

// Get the number of milliseconds since library initialization.
FRAMEWORK_API unsigned int getTickCount();
FRAMEWORK_API int run(Framework*);
