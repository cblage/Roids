#include "Particle.h"

namespace asteroids {

	Particle::Particle(std::string id, ParticleManager * particleManager) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(1),
		_penetrationTime(0),
		_maxPenetrationTime(cg::Properties::instance()->getDouble("PARTICLE_MAX_PENETRATE")),
		PhysicsObject() {};

	Particle::Particle(std::string id, double strength, ParticleManager * particleManager) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(strength),
		_penetrationTime(0),
		_maxPenetrationTime(cg::Properties::instance()->getDouble("PARTICLE_MAX_PENETRATE")),
		PhysicsObject() {};
	
	Particle::Particle(std::string id, ParticleManager * particleManager, double mass) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(1),
		_penetrationTime(0),
		_maxPenetrationTime(cg::Properties::instance()->getDouble("PARTICLE_MAX_PENETRATE")),
		PhysicsObject(mass) {};

	Particle::Particle(std::string id, double strength, ParticleManager * particleManager, double mass) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(strength),
		_penetrationTime(0),
		_maxPenetrationTime(cg::Properties::instance()->getDouble("PARTICLE_MAX_PENETRATE")),
		PhysicsObject(mass) {};

	Particle::~Particle() {
	}

	void Particle::setDestroyed(bool destroyed) {
		_destroyed = destroyed;
	}
	
	bool Particle::isDestroyed(void){
		return _destroyed;
	}
	
	ParticleManager * Particle::getParticleManager(void) {
		return _particleManager;
	}

	void Particle::setStrength(double strength) {
		_strength = strength;
	}
	double Particle::getStrength(void) {
		return _strength;
	}

	void Particle::setHealth(double health) {
		_health = health;
		if(_health < 1) {
			destroy();
		}
	}

	double Particle::getHealth(void) {
		return _health;
	}

	void Particle::checkCollisions(double long elapsed_millis) {
		if(isDestroyed() == true)
			return;

		std::vector<Particle*> particles = getParticleManager()->getParticles();
		for(std::vector<Particle*>::size_type i = 0; i < particles.size(); i++) {
				if(particles[i]->getId() == _id) continue;
				if(collidesWith(particles[i]) && !particles[i]->isDestroyed()) {
						double myCollisionFactor = (particles[i]->getStrength()/getStrength()) * (particles[i]->getMass()/getMass()) * length(particles[i]->getVelocity() - getVelocity());
						double theirCollisionFactor = (getStrength()/particles[i]->getStrength()) * (getMass()/particles[i]->getMass()) * length(particles[i]->getVelocity() - getVelocity());
						calculateCollision(particles[i]);
						setHealth(getHealth() - myCollisionFactor * getHealth());
						particles[i]->setHealth(particles[i]->getHealth() - theirCollisionFactor * particles[i]->getHealth());
				}
				if(penetrates(particles[i])) {
					_penetrationTime += elapsed_millis / 1000.0;
				} 
		}

		if(_penetrationTime > _maxPenetrationTime) {
			destroy();
		}
	}

	void Particle::destroy(void) {
		setDestroyed(true);
		getParticleManager()->destroyParticle(getId());
	}
}
