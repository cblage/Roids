#include "ParticleManager.h"

namespace asteroids {

	ParticleManager::ParticleManager(std::string id) : cg::Group(id), _currIdNum(0) {
	}
	ParticleManager::~ParticleManager() {
		_newParticles.clear();
		for (std::vector<std::string>::iterator p = _deletedParticles.begin( ); p != _deletedParticles.end(); ++p) {
			destroy(*p);
		}
		_deletedParticles.clear();
	}
	void ParticleManager::createEntities() {
		createAsteroids(cg::Properties::instance()->getInt("DEMO_ASTEROIDS"));
	}
	void ParticleManager::postInit() {
		std::ostringstream os;
		os << size() << " particles on screen.";
		_numParticlesMessage = os.str();
	}
	void ParticleManager::preDrawOverlay() {
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
	
	Particle * ParticleManager::getParticle(std::string id) {
		return dynamic_cast<Particle *>(get(id));
	}
	
	void ParticleManager::addParticle(Particle * p) {
		_newParticles.push_back(p);
	}

	void ParticleManager::postUpdate(unsigned long elapsed_millis) {

	}

	void ParticleManager::createAsteroids(unsigned int numAsteroids, double scaleFactor, double radius, cg::Vector2d position, double scaleDelta) {
		double x, y, angle;
		cg::Vector2d newPosition, velocity;
		double rand, rand2, scaleRand, finalScaleFactor;
		rand = randomBetween(0, 3.14);
		scaleFactor = (scaleFactor < 1) ? 1 : scaleFactor;
		scaleDelta = abs(scaleDelta);
		for(unsigned int i = 0; i < numAsteroids; i++) {
			scaleRand = (scaleDelta > 0) ? randomBetween(-scaleDelta, scaleDelta) : 0;
			finalScaleFactor = ((scaleFactor + scaleRand) > 1) ? scaleFactor + scaleRand : scaleFactor + randomBetween(0, scaleDelta);
			
			rand2 = randomBetween(0.1,7.0)/5.0;
 			angle = 2*(3.14)*i/numAsteroids + rand + rand2;
			x = cos(angle)*randomBetween(0.5,0.9)*radius;
			y = sin(angle)*randomBetween(0.5,0.9)*radius;
			
			newPosition = position + cg::Vector2d(x,y);
			velocity = normalize(cg::Vector2d(x,y))*randomBetween(50,200); 
			createAsteroid(finalScaleFactor, newPosition, velocity);
		}
	}

	void ParticleManager::createAsteroids(unsigned int numAsteroids) {
		int quadrant = 0;
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		for(unsigned int i = 0; i < numAsteroids; i++) {
			switch (quadrant)	{
				case 0:
					createAsteroid(cg::Vector2d((win.width*randomBetween(0.0,0.33)),(win.height*randomBetween(0.0,0.33))));
					break;
				case 1:
					createAsteroid(cg::Vector2d((win.width*randomBetween(0.67,1)),(win.height*randomBetween(0.67,1))));
					break;
				case 2:
					createAsteroid(cg::Vector2d((win.width*randomBetween(0.0,0.33)),(win.height*randomBetween(0.67,1))));
					break;
				case 3:
					createAsteroid(cg::Vector2d((win.width*randomBetween(0.33,0.67)),(win.height*randomBetween(0.0,0.33))));
					break;
				case 4:
					createAsteroid(cg::Vector2d((win.width*randomBetween(0.33,0.67)),(win.height*randomBetween(0.67,1))));
					break;
				case 5:
					createAsteroid(cg::Vector2d((win.width*randomBetween(0.33,0.67)),(win.height*randomBetween(0.33,0.67))));
					break;
				case 6:
					createAsteroid(cg::Vector2d((win.width*randomBetween(0.0,0.33)),(win.height*randomBetween(0.33,0.67))));
					break;
				case 7:
					createAsteroid(cg::Vector2d((win.width*randomBetween(0.67,1)),(win.height*randomBetween(0.33,0.67))));
					break;
			}
			quadrant = (quadrant + 1) % 8;
		}
	}

	void ParticleManager::createAsteroids(unsigned int numAsteroids, double scaleFactor, double scaleDelta) {
		int quadrant = 0;
		double scaleRand, finalScaleFactor;
		scaleFactor = (scaleFactor < 1) ? 1 : scaleFactor;
		scaleDelta = abs(scaleDelta);
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		for(unsigned int i = 0; i < numAsteroids; i++) {
			scaleRand = (scaleDelta > 0) ? randomBetween(-scaleDelta, scaleDelta) : 0;
			finalScaleFactor = ((scaleFactor + scaleRand) > 1) ? scaleFactor + scaleRand : scaleFactor + randomBetween(0, scaleDelta);
			switch (quadrant)	{
				case 0:
					createAsteroid(finalScaleFactor, cg::Vector2d((win.width*randomBetween(0.0,0.33)),(win.height*randomBetween(0.0,0.33))));
					break;
				case 1:
					createAsteroid(finalScaleFactor, cg::Vector2d((win.width*randomBetween(0.67,1)),(win.height*randomBetween(0.67,1))));
					break;
				case 2:
					createAsteroid(finalScaleFactor, cg::Vector2d((win.width*randomBetween(0.0,0.33)),(win.height*randomBetween(0.67,1))));
					break;
				case 3:
					createAsteroid(finalScaleFactor, cg::Vector2d((win.width*randomBetween(0.33,0.67)),(win.height*randomBetween(0.0,0.33))));
					break;
				case 4:
					createAsteroid(finalScaleFactor, cg::Vector2d((win.width*randomBetween(0.33,0.67)),(win.height*randomBetween(0.67,1))));
					break;
				case 5:
					createAsteroid(finalScaleFactor, cg::Vector2d((win.width*randomBetween(0.33,0.67)),(win.height*randomBetween(0.33,0.67))));
					break;
				case 6:
					createAsteroid(finalScaleFactor, cg::Vector2d((win.width*randomBetween(0.0,0.33)),(win.height*randomBetween(0.33,0.67))));
					break;
				case 7:
					createAsteroid(finalScaleFactor, cg::Vector2d((win.width*randomBetween(0.67,1)),(win.height*randomBetween(0.33,0.67))));
					break;
			}
			quadrant = (quadrant + 1) % 8;
		}
	}

	void ParticleManager::createAsteroid(double scaleFactor, cg::Vector2d position) {
		scaleFactor = (scaleFactor < 1) ? 1 : scaleFactor;
		std::ostringstream os;
		os << "Asteroid" << _currIdNum++;
		Asteroid * createdAsteroid = new Asteroid(os.str(), scaleFactor, this);
		createdAsteroid->init();
		createdAsteroid->accelerate(randomBetween(-400, 400), false);
		createdAsteroid->setPosition(position);
		addParticle(createdAsteroid);
	}

	void ParticleManager::createAsteroid(double scaleFactor, cg::Vector2d position, cg::Vector2d velocity) {
		scaleFactor = (scaleFactor < 1) ? 1 : scaleFactor;
		std::ostringstream os;
		os << "Asteroid" << _currIdNum++;
		Asteroid * createdAsteroid = new Asteroid(os.str(), scaleFactor, this);
		createdAsteroid->init();
		createdAsteroid->setVelocity(velocity);
		createdAsteroid->setPosition(position);
		addParticle(createdAsteroid);
	}

	void ParticleManager::createAsteroid(cg::Vector2d position) {
		std::ostringstream os;
		os << "Asteroid" << _currIdNum++;
		Asteroid * createdAsteroid = new Asteroid(os.str(), this);
		createdAsteroid->init();
		createdAsteroid->accelerate(randomBetween(-400, 400), false);
		createdAsteroid->setPosition(position);
		addParticle(createdAsteroid);
	}

	void ParticleManager::createAsteroid(void) {
		std::ostringstream os;
		os << "Asteroid" << _currIdNum++;
		Asteroid * createdAsteroid = new Asteroid(os.str(), this);
		createdAsteroid->init();
		createdAsteroid->accelerate(randomBetween(-400, 400), false);
		addParticle(createdAsteroid);
	}

	void ParticleManager::createLaserShot(cg::Vector2d position, double radiansRotation, cg::Vector2d velocity, double degreesRotation) {
		std::ostringstream os;
		os << "LaserShot" << _currIdNum++;
		LaserShot * newLaserShot = new LaserShot(os.str(), this);
		newLaserShot->init();
		newLaserShot->setPosition(position);
		newLaserShot->setRotation(radiansRotation);
		newLaserShot->setVelocity(velocity);
		if (degreesRotation >= 180 && degreesRotation < 360) {
			newLaserShot->accelerate(-1000 * newLaserShot->getMass(), true);
		} else {
			newLaserShot->accelerate(1000 * newLaserShot->getMass(), true);
		} 
		addParticle(newLaserShot);
	}

	void ParticleManager::createShip(cg::Vector2d position, double radiansRotation, cg::Vector2d velocity, double degreesRotation) {
		std::ostringstream os;
		os << "Ship" << _currIdNum++;
		SpaceShip * newShip = new SpaceShip(os.str(), this);
		newShip->init();
		newShip->setPosition(position);
		newShip->setRotation(radiansRotation);
		newShip->setVelocity(velocity);
		addParticle(newShip);
	}

	void ParticleManager::createShip(void) {
		std::ostringstream os;
		os << "Ship" << _currIdNum++;
		SpaceShip * newShip = new SpaceShip(os.str(), this);
		newShip->init();
		addParticle(newShip);
	}

	double ParticleManager::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}

}