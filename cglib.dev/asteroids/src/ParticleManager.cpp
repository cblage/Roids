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

	std::vector<Particle*> ParticleManager::getParticles() {
		//ODEIO-TE ENTITIES!!!!!!!!!!!!!!
		std::vector<Particle*> particles;
		for (std::vector<Entity*>::iterator p = cg::Group::begin(); p != cg::Group::end( ); p++) {
			particles.push_back(dynamic_cast<Particle*>(*p));
		}
		return particles;

		//return new std::vector<Particle*>(*(cg::Group::getEntities())); 
	}

	void ParticleManager::postUpdate(unsigned long elapsed_millis) {
		std::vector<Particle*> particles = getParticles();
		for(std::vector<Particle*>::size_type i = 0; i < particles.size(); i++) {
			for(std::vector<Particle*>::size_type j = i+1; j < particles.size(); j++) {
				if(particles[i]->collidesWith(particles[j])) {
					if((particles[i]->getStrength() != particles[j]->getStrength())) {
						particles[i]->setDestroyed(true);
						destroyParticle(particles[i]->getId());
						particles[j]->setDestroyed(true);
						destroyParticle(particles[j]->getId());
					} else {
						particles[i]->calculateCollision(particles[j]);
					}
				}
			}
		}
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
	
	void ParticleManager::createLaserShot(cg::Vector2d position, double radiansRotation) {
		std::ostringstream os;
		os << "Particle" << _currIdNum++;
		LaserShot * newLaserShot = new LaserShot(os.str(), this);
		newLaserShot->init();
		newLaserShot->setPosition(position);
		newLaserShot->setRotation(radiansRotation);
		newLaserShot->accelerate(500, true);
		_newParticles.push_back(newLaserShot);
	}

	double ParticleManager::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}

	SpaceShip * ParticleManager::getSpaceShip(void) {
		return _ship;
	}
}