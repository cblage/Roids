#pragma once
#ifndef MY_APP_H
#define MY_APP_H
#pragma message("MyApp is included")

#include "cg/cg.h"
#include "MyCamera.h"
#include "SpaceShip.h"
#include "GameController.h"
#include "StarSphere.h"
#include "ParticleManager.h"
#include "Lights.h"

namespace asteroids {
	class StarSphere;
	class GameController;
	class MyCamera;
	class ParticleManager;
	class SpaceShip;

	class MyApp : public cg::Application {
	public:
		MyApp();
		~MyApp();
		void createEntities();
	};
}

#endif
