#include "Particle.h"

namespace asteroids {

	Particle::Particle(std::string id, ParticleManager * particleManager) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(0),
		_penetrationTime(0),
		PhysicsObject() {};

	Particle::Particle(std::string id, double strength, ParticleManager * particleManager) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(strength),
		_penetrationTime(0),
		PhysicsObject() {};
	
	Particle::Particle(std::string id, ParticleManager * particleManager, double mass) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(0),
		_penetrationTime(0),
		PhysicsObject(mass) {};

	Particle::Particle(std::string id, double strength, ParticleManager * particleManager, double mass) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(strength),
		_penetrationTime(0),
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

	void Particle::checkCollisions(double long elapsed_millis) {
		if(isDestroyed() == true)
			return;

		std::vector<Particle*> particles = getParticleManager()->getParticles();
		for(std::vector<Particle*>::size_type i = 0; i < particles.size(); i++) {
				if(particles[i]->getId() == _id) continue;
				if(collidesWith(particles[i])) {
					if((getStrength() < particles[i]->getStrength())) {
						destroy();
						particles[i]->destroy();
					} else {
						calculateCollision(particles[i]);
					}
				}
				if(penetrates(particles[i])) {
					_penetrationTime += elapsed_millis / 1000.0;
				} 
		}

		if(collidesWith(getParticleManager()->getSpaceShip()) || _penetrationTime > 0.4) {
			destroy();
		}
	}

	void Particle::destroy(void) {
		setDestroyed(true);
		getParticleManager()->destroyParticle(getId());
	}
}
