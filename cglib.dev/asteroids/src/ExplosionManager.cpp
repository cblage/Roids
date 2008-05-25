#include "ExplosionManager.h"

namespace asteroids {
	ExplosionManager::ExplosionManager(std::string id, MyApp *application) : ParticleManager(id), _application(application) {

	}
	ExplosionManager::~ExplosionManager() {
	}
	
	void ExplosionManager::createEntities() {

	}

	void ExplosionManager::generateExplosion(Particle * p) { //generates an explosion for the given particle
	
	}
	
	void ExplosionManager::createExplosionDebris(cg::Vector2d position, cg::Vector2d velocity) {
		/*std::ostringstream os;
		os << "ExpDebris" << _currIdNum++;
		ExplosionDebris * createdExplosionDebris = new ExplosionDebris(os.str(), this);
		createdExplosionDebris->init();
		createdExplosionDebris->setVelocity(velocity);
		createdExplosionDebris->setPosition(position);
		addParticle(createdExplosionDebris);*/
	}

	void ExplosionManager::createExplosionCenter(cg::Vector2d position, cg::Vector2d velocity) {
		/*std::ostringstream os;
		os << "ExpCenter" << _currIdNum++;
		ExplosionCenter * createdExplosionCenter = new ExplosionCenter(os.str(), this);
		createdExplosionCenter->init();
		createdExplosionCenter->setVelocity(velocity);
		createdExplosionCenter->setPosition(position);
		addParticle(createdExplosionDebris);*/
	}


	void ExplosionManager::preDrawOverlay() {
		
	}

}