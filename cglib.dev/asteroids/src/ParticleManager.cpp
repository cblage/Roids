#include "ParticleManager.h"

namespace asteroids {

	ParticleManager::ParticleManager(std::string id, SpaceShip * ship) : cg::Group(id), _currIdNum(0), _ship(ship) {
	}
	ParticleManager::~ParticleManager() {
	}
	void ParticleManager::createEntities() {
		int nasteroids = cg::Properties::instance()->getInt("NASTEROIDS");
		for(int i = 0; i < nasteroids; i++) {
			std::ostringstream os;
			os << "Particle" << _currIdNum++;
			add(new Asteroid(os.str(), this));
		}
	}
	void ParticleManager::postInit() {
        std::ostringstream os;
        os << size() << " particles on screen.";
		_numParticlesMessage = os.str();
	}
	void ParticleManager::drawOverlay() {
		glColor3d(0.9,0.1,0.1);
		cg::Util::instance()->drawBitmapString(_numParticlesMessage,10,20);
	}
	
	void ParticleManager::destroyParticle(std::string id) {
		_deletedParticles.push_back(id);
	}

	void ParticleManager::preUpdate(unsigned long elapsed_millis) {
		for (std::vector<std::string>::iterator p = _deletedParticles.begin( ); p != _deletedParticles.end(); ++p) {
		  destroy(*p);
		}
		_deletedParticles.clear();
		for (std::vector<Particle*>::iterator q = _newParticles.begin( ); q != _newParticles.end(); ++q) {
		  add(*q);
		}
		_newParticles.clear();

		std::ostringstream os;
        os << size() << " particles on screen.";
		_numParticlesMessage = os.str();
	}

	void ParticleManager::createAsteroids(unsigned int numAsteroids, double scaleFactor, cg::Vector2d position) {
		for(unsigned int i = 0; i < numAsteroids; i++) {
			std::ostringstream os;
			os << "Particle" << _currIdNum++;
			Asteroid * createdAsteroid = new Asteroid(os.str(), scaleFactor, this);
			createdAsteroid->init();
			createdAsteroid->accelerate(randomBetween(200, 400), false);
			createdAsteroid->setPosition(position);
			_newParticles.push_back(createdAsteroid);
		}
	}
	
	double ParticleManager::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}

	SpaceShip * ParticleManager::getSpaceShip(void) {
		return _ship;
	}
}