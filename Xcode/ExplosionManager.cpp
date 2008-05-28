#include "ExplosionManager.h"

namespace asteroids {
	ExplosionManager::ExplosionManager(std::string id, MyApp *application) : ParticleManager(id), _application(application) {

	}
	ExplosionManager::~ExplosionManager() {
	}
	
	void ExplosionManager::createEntities() {

	}

	void ExplosionManager::generateExplosion(Particle * p) { //generates an explosion for the given particle
		if(p->getParticleType() == 'l') {
			return;
		}
		double x, y, angle;
		cg::Vector2d newPosition, velocity;
		double rand, rand2;
		rand = randomBetween(0, 3.14);
		unsigned int numDebris = ceil(p->getMass()/50);
		for(unsigned int i = 0; i < numDebris; i++) {
			rand2 = randomBetween(0.1,7.0)/5.0;
 			angle = 2*(3.14)*i/numDebris+ rand + rand2;
			x = cos(angle)*randomBetween(0.5,0.9)*p->getCollisionRadius();
			y = sin(angle)*randomBetween(0.5,0.9)*p->getCollisionRadius();
			
			newPosition = p->getPosition() + cg::Vector2d(x,y);
			velocity = normalize(cg::Vector2d(x,y))*randomBetween(50,200)+p->getVelocity(); 
			createExplosionDebris(newPosition, velocity);
		}
	}
	
	void ExplosionManager::createExplosionDebris(cg::Vector2d position, cg::Vector2d velocity, cg::Vector3d color) {
		std::ostringstream os;
		os << "ExplosionDebris" << _currIdNum++;
		ExplosionDebris * createdExplosionDebris = new ExplosionDebris(os.str(), this);
		createdExplosionDebris->init();
		createdExplosionDebris->setVelocity(velocity);
		createdExplosionDebris->setPosition(position);
		addParticle(createdExplosionDebris);
	}
	
	void ExplosionManager::clearExplosions() {
			//make sure we have a clean slate - no new particles are going to be added
		//and we dont want duplicates in the deleted ones
		_newParticles.clear();
		_deletedParticles.clear();
		
		std::vector<Particle *> particles = getParticles();
		for(std::vector<Particle*>::size_type i = 0; i < particles.size(); i++) {
			//cant use this because asteroids would generate new ones
			//particles[i]->destroy();
			destroyParticle(particles[i]->getId());
		}
	}

	void ExplosionManager::preDrawOverlay() {
		
	}

}