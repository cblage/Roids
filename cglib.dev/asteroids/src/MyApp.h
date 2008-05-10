#ifndef MY_APP_H
#define MY_APP_H

#include "cg/cg.h"
#include "MyBat.h"
#include "MyBoxManager.h"
#include "MyCamera.h"
#include "GameController.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "StarSphere.h"
#include "ParticleManager.h"

namespace asteroids {

	class MyApp : public cg::Application {
	public:
		MyApp();
		~MyApp();
		void createEntities();
	};
}

#endif
