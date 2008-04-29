#include "PhysicsEngine.h"

namespace asteroids {

	PhysicsEngine::PhysicsEngine(){
		_velocity = cg::Vector2d( 0, 0);
		_position = cg::Vector2d( 0, 0);
		_acelFactor = 0;
		_minVelocity = cg::Vector2d( 0, 0); 
		_acceleration = cg::Vector2d( 0, 0);
		_withRotation = false; 
		_withMinVelocity = false;
		_accelerating = false;
		_rotFactor = 0;
		_rotationDeg = 0;
		_rotationRad = 0;
		_rotating = false;
		_collisionCenter = cg::Vector2d(0,0);
		_collisionRadius = 0;
		_universeWidth = 0;
		_universeHeight = 0;
	}
	PhysicsEngine::PhysicsEngine(cg::Vector2d velocity,cg::Vector2d position){
		_velocity = velocity;
		_position = position;
		_acelFactor = 0;
		_minVelocity = cg::Vector2d( 0, 0); 
		_acceleration = cg::Vector2d( 0, 0);
		_withRotation = false; 
		_withMinVelocity = false;
		_accelerating = false;
		_rotFactor = 0;
		_rotationDeg = 0;
		_rotationRad = 0;
		_rotating = false;
		_collisionCenter = cg::Vector2d(0,0);
		_collisionRadius = 0;
		_universeWidth = 0;
		_universeHeight = 0;
	}

	PhysicsEngine::~PhysicsEngine(){
	}
	
	void PhysicsEngine::setUniverseDimensions(int width, int height) {
		_universeWidth = width;
		_universeHeight = height;
	}

	void PhysicsEngine::setVelocity(cg::Vector2d velocity) {
		_velocity = velocity;
	}

	void PhysicsEngine::setPosition(cg::Vector2d position) {
		_position = position;
	}
	
	cg::Vector2d PhysicsEngine::getUniverseDimensions(void) {
		return cg::Vector2d(_universeWidth, _universeHeight);
	}


	cg::Vector2d PhysicsEngine::getNormalizedVelocity() const {
		return normalize(_velocity);
	}

	void PhysicsEngine::startAcceleration(double factor, bool withRotation) {
		_accelerating = true;
		_acelFactor = factor;
		_withMinVelocity = false;
		_withRotation = withRotation;		
	}

	void PhysicsEngine::startAcceleration(double factor, bool withRotation, cg::Vector2d minVelocity) {
		_acelFactor = factor;
		_withMinVelocity = true;
		_minVelocity = minVelocity;
		_withRotation = withRotation;
		_accelerating = true;
	}

	void PhysicsEngine::stopAcceleration() {
		_accelerating = false;
	}

	void PhysicsEngine::update(double elapsed_millis) {
		double elapsed_seconds = elapsed_millis / 1000.0;
		setCollisionCenter(getPosition());

		//ROTATION UPDATE
		if(_rotating == true)
			rotate(_rotFactor*elapsed_seconds);
		
		if(_accelerating == true) {
			if(_withMinVelocity == true) {
				accelerate(_acelFactor*elapsed_seconds, _withRotation, _minVelocity);
			} else {
				accelerate(_acelFactor*elapsed_seconds, _withRotation);
			}
		}
		// update dos objectos
		_position += _velocity * elapsed_seconds;

		if(_position[0] < 0) { 
			_position[0] = _universeWidth;
		}
		if(_position[0] > _universeWidth) { 
			_position[0] = 0;
			}
		if(_position[1] < 0) { 
			_position[1] = _universeHeight;
		}
		if(_position[1] > _universeHeight) { 
			_position[1] = 0;
		}
	}

	void PhysicsEngine::accelerate(double factor, bool withRotation) {
		if(withRotation == true) {
			_acceleration = cg::Vector2d(cos(getRotation()), sin(getRotation())) * factor;
		} else {
			_acceleration = getNormalizedVelocity()  * factor;
		}

		cg::Vector2d newVelocity = _velocity + _acceleration;
		if(abs(newVelocity[0]) < 1) {
			newVelocity[0] = 0;
			_acceleration[0] = 0;
		} 
		if(abs(newVelocity[1]) < 1) {
			newVelocity[1] = 0;
			_acceleration[1] = 0;
		} 		
		_velocity = newVelocity;
	}

	void PhysicsEngine::accelerate(double factor, bool withRotation, cg::Vector2d minVelocity) {
		if(withRotation == true) {
			_acceleration = cg::Vector2d(cos(getRotation()), sin(getRotation())) * factor;
		} else {
			_acceleration = getNormalizedVelocity() * factor;
		}
		cg::Vector2d newVelocity = _velocity + _acceleration;
		if(abs(newVelocity[0]) < minVelocity[0] || abs(newVelocity[0]) < 5) {
			newVelocity[0] = 0;
			_acceleration[0] = 0;
		} 
		if(abs(newVelocity[1]) < minVelocity[1] || abs(newVelocity[1]) < 5) {
			newVelocity[1] = 0;
			_acceleration[1] = 0;
		} 		

		_velocity = newVelocity;
	}

	cg::Vector2d PhysicsEngine::getAcceleration() const {
		return _acceleration;
	}

	cg::Vector2d PhysicsEngine::getVelocity() const {
		return _velocity;
	}

	cg::Vector2d PhysicsEngine::getPosition() const {
		return _position;
	}

	void PhysicsEngine::startRotator(double factor) {
		_rotating = true;
		_rotFactor = factor;
	}

	void PhysicsEngine::stopRotator() {
		_rotating = false;
	}

	void PhysicsEngine::rotate(double factor) {
		_rotationDeg = fmod(_rotationDeg + factor, 360);
		_rotationRad = _rotationDeg * PI4 / 180;
	}

	double PhysicsEngine::getRotation() const {
		return _rotationRad;
	}
	double PhysicsEngine::getRotation(bool inDegrees) const {
		return (inDegrees == true) ? _rotationDeg : _rotationRad;
	}

	double PhysicsEngine::getCollisionRadius() { 
		return _collisionRadius;
	}
	cg::Vector2d PhysicsEngine::getCollisionCenter() { 
		return _collisionCenter;
	}
	void PhysicsEngine::setCollisionRadius(double collisionRadius) { 
		_collisionRadius = collisionRadius;
	}
	void PhysicsEngine::setCollisionCenter(cg::Vector2d collisionCenter) {
		_collisionCenter = collisionCenter;
	}
	bool PhysicsEngine::collidesWith(PhysicsObject *pobject) {
		return (length(pobject->getCollisionCenter() - getCollisionCenter()) <= pobject->getCollisionRadius() + getCollisionRadius());
	}


}
	