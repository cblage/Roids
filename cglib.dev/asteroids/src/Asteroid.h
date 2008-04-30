#ifndef ASTEROID_H
#define ASTEROID_H

#include <string>
#include <vector>
#include "cg/cg.h"
#include <cmath>
#include "AsteroidManager.h"
#include "SpaceShip.h"
#include "PhysicsEngine.h"

namespace asteroids {
	class AsteroidManager;
	class Asteroid : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener,
		public cg::IMouseEventListener,
		public PhysicsObject
	{
	private:
		std::vector<cg::Vector3d> _asteroid_vector;
		cg::Vector2d _size;
		double _scaleFactor, _radius;		
		bool _destroyed;
		AsteroidManager * _asteroidManager;
		SpaceShip * _ship;
	public:
		Asteroid(std::string id, double scaleFactor, SpaceShip * ship);
		Asteroid(std::string id, AsteroidManager * asteroidManager, SpaceShip * ship);
		Asteroid(std::string id, SpaceShip * ship);
		Asteroid(std::string id, double scaleFactor, AsteroidManager * asteroidManager, SpaceShip * ship);
		~Asteroid();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
        void onReshape(int width, int height);
		double randomBetween(double min, double max);
		void onMouse(int button, int state, int x, int y);
        void onMouseMotion(int x, int y);
        void onMousePassiveMotion(int x, int y);
	};
}

#endif