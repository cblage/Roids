#include "ParticleManager.h"

namespace asteroids {

	ParticleManager::ParticleManager(std::string id) : cg::Group(id), _currIdNum(0) {
	}
	ParticleManager::~ParticleManager() {
	}
	void ParticleManager::createEntities() {
		int nasteroids = cg::Properties::instance()->getInt("NASTEROIDS");
		for(int i = 0; i < nasteroids; i++) {
			createAsteroid();
		}
		createShip();
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
	}

	void ParticleManager::postUpdate(unsigned long elapsed_millis) {

	}

	void ParticleManager::createAsteroids(unsigned int numAsteroids, double scaleFactor, cg::Vector2d position) {
		for(unsigned int i = 0; i < numAsteroids; i++) {
			createAsteroid(scaleFactor, position);
		}
	}

	void ParticleManager::createAsteroid(double scaleFactor, cg::Vector2d position) {
		std::ostringstream os;
		os << "Asteroid" << _currIdNum++;
		Asteroid * createdAsteroid = new Asteroid(os.str(), scaleFactor, this);
		createdAsteroid->init();
		createdAsteroid->accelerate(randomBetween(-400, 400), false);
		createdAsteroid->setPosition(position);
		_newParticles.push_back(createdAsteroid);
	}
	
	void ParticleManager::createAsteroid(void) {
		std::ostringstream os;
		os << "Asteroid" << _currIdNum++;
		Asteroid * createdAsteroid = new Asteroid(os.str(), this);
		createdAsteroid->init();
		createdAsteroid->accelerate(randomBetween(-400, 400), false);
		_newParticles.push_back(createdAsteroid);
	}
	void ParticleManager::createLaserShot(cg::Vector2d position, double radiansRotation, cg::Vector2d velocity, double degreesRotation) {
		std::ostringstream os;
		os << "LaserShot" << _currIdNum++;
		LaserShot * newLaserShot = new LaserShot(os.str(), this);
		newLaserShot->init();
		newLaserShot->setPosition(position);
		newLaserShot->setRotation(radiansRotation);
		newLaserShot->setVelocity(velocity);
		if (degreesRotation >= 180 && degreesRotation < 360)
			newLaserShot->accelerate(-500, true);
		else 
			newLaserShot->accelerate(500, true);
		_newParticles.push_back(newLaserShot);
	}

	void ParticleManager::createShip(cg::Vector2d position, double radiansRotation, cg::Vector2d velocity, double degreesRotation) {
		std::ostringstream os;
		os << "Ship" << _currIdNum++;
		SpaceShip * newShip = new SpaceShip(os.str(), this);
		newShip->init();
		newShip->setPosition(position);
		newShip->setRotation(radiansRotation);
		newShip->setVelocity(velocity);
		_newParticles.push_back(newShip);
	}

	void ParticleManager::createShip(void) {
		std::ostringstream os;
		os << "Ship" << _currIdNum++;
		SpaceShip * newShip = new SpaceShip(os.str(), this);
		newShip->init();
		_newParticles.push_back(newShip);
	}
	double ParticleManager::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}

}