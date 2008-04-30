#ifndef ASTEROID_MANAGER_H
#define ASTEROID_MANAGER_H

#include <sstream>
#include <string>
#include <vector>
#include "cg/cg.h"
#include "Asteroid.h"
#include "SpaceShip.h"

namespace asteroids {
	class Asteroid;

	class AsteroidManager : public cg::Group,
		public cg::GroupDraw,
		public cg::GroupUpdate,
		public cg::GroupReshapeEvent,
		public cg::IDrawOverlayListener,
		public cg::GroupMouseEvent
	{
	private:
		std::string _numAsteroidMessage;
		std::vector<std::string> _deletedAsteroids;
		std::vector<Asteroid*> _newAsteroids;
		unsigned int _currIdNum;
		SpaceShip * _ship;
	protected:
		void createEntities();
		void postInit();
	public:
		AsteroidManager(std::string id, SpaceShip * ship);
		~AsteroidManager();
		void destroyAsteroid(std::string id);
		void drawOverlay();
		void preUpdate(unsigned long elapsed_millis);
		void createAsteroids(unsigned int numAsteroids, double scaleFactor, cg::Vector2d position);
		double randomBetween(double min, double max);
	};
}

#endif