#include "AsteroidManager.h"

namespace asteroids {

	AsteroidManager::AsteroidManager(std::string id, SpaceShip * ship) : cg::Group(id), _currIdNum(0), _ship(ship) {
	}
	AsteroidManager::~AsteroidManager() {
	}
	void AsteroidManager::createEntities() {
		int nasteroids = cg::Properties::instance()->getInt("NASTEROIDS");
		for(int i = 0; i < nasteroids; i++) {
			std::ostringstream os;
			os << "Asteroid" << _currIdNum++;
			add(new Asteroid(os.str(), this, _ship));
		}
	}
	void AsteroidManager::postInit() {
        std::ostringstream os;
        os << size() << " asteroids on screen.";
		_numAsteroidMessage = os.str();
	}
	void AsteroidManager::drawOverlay() {
		glColor3d(0.9,0.1,0.1);
		cg::Util::instance()->drawBitmapString(_numAsteroidMessage,10,20);
	}
	
	void AsteroidManager::destroyAsteroid(std::string id) {
		_deletedAsteroids.push_back(id);
		//destroy(id);
		//remove(id);
	}
	void AsteroidManager::preUpdate(unsigned long elapsed_millis) {
		for (std::vector<std::string>::iterator p = _deletedAsteroids.begin( ); p != _deletedAsteroids.end(); ++p) {
		  destroy(*p);
		}
		_deletedAsteroids.clear();
		for (std::vector<Asteroid*>::iterator q = _newAsteroids.begin( ); q != _newAsteroids.end(); ++q) {
		  add(*q);
		}
		_newAsteroids.clear();

		std::ostringstream os;
        os << size() << " asteroids on screen.";
		_numAsteroidMessage = os.str();
	}

	void AsteroidManager::createAsteroids(unsigned int numAsteroids, double scaleFactor, cg::Vector2d position) {
		for(unsigned int i = 0; i < numAsteroids; i++) {
			std::ostringstream os;
			os << "Asteroid" << _currIdNum++;
			Asteroid * createdAsteroid = new Asteroid(os.str(), scaleFactor, this, _ship);
			createdAsteroid->init();
			createdAsteroid->accelerate(randomBetween(200, 400), false);
			createdAsteroid->setPosition(position);
			_newAsteroids.push_back(createdAsteroid);
		}
	}
	
	double AsteroidManager::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}
}