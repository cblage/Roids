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
		_mass = 1;
		_hasUpdated = false;
	}
	
	PhysicsEngine::PhysicsEngine(double mass) {
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
		_mass = mass;
		_hasUpdated = false;
	}
	

	PhysicsEngine::PhysicsEngine(cg::Vector2d velocity,cg::Vector2d position) {
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
		_hasUpdated = false;
		_mass = 1;	
	}
	PhysicsEngine::PhysicsEngine(cg::Vector2d velocity,cg::Vector2d position, double mass) {
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
		_mass = mass;	
		_hasUpdated = false;
	}

	PhysicsEngine::~PhysicsEngine(){
	}
	
	double PhysicsEngine::getMass(void) {
		return _mass;
	}
	
	void PhysicsEngine::setMass(double mass) {
		_mass = mass;
	}

	void PhysicsEngine::setUniverseDimensions(int width, int height) {
		_universeWidth = width;
		_universeHeight = height;
	}

	void PhysicsEngine::setVelocity(cg::Vector2d velocity) {
		_velocity = velocity;
	}

	void PhysicsEngine::setPosition(cg::Vector2d position) {
		_position = constrainVector(position);
	}
	
	void PhysicsEngine::setAcceleration(cg::Vector2d acceleration) {
		_acceleration = acceleration;
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

	double PhysicsEngine::realMod(double x, double y) {
		return x - y * floor(x / y);
	}

	cg::Vector2d PhysicsEngine::constrainVector(cg::Vector2d vector) {
		vector[0] = realMod(vector[0], _universeWidth);
		vector[1] = realMod(vector[1], _universeHeight);
		return vector;
	}

	double PhysicsEngine::getDistance(cg::Vector2d vectorA, cg::Vector2d vectorB) {
		double x = std::min(realMod(abs(vectorA[0]-vectorB[0])+_universeWidth, _universeWidth), realMod(_universeWidth-abs(vectorA[0]-vectorB[0]), _universeWidth));
		double y = std::min(realMod(abs(vectorA[1]-vectorB[1])+_universeHeight, _universeHeight), realMod(_universeHeight-abs(vectorA[1]-vectorB[1]), _universeHeight));
		return sqrt(pow(x,2)+pow(y,2));	
	}
	void PhysicsEngine::update(double elapsed_millis) {
		_hasUpdated = true;
		_previousElapsedMillis = elapsed_millis;
		_previousVelocity = _velocity;
		_previousAcceleration = _acceleration;
		_previousPosition = _position;
		_previousRotationRad = _rotationRad;
		_previousCollisionCenter = _collisionCenter;

		double elapsed_seconds = elapsed_millis / 1000.0;


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

		_position = constrainVector(_position);
		



		/*if(_position[0] < 0) { 
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
		}*/
		setCollisionCenter(getPosition());
	}
	
	void PhysicsEngine::stepBack(void) {
		if(_hasUpdated == false)
			return;

		setPosition(_previousPosition);
		setRotation(_previousRotationRad);
		setVelocity(_previousVelocity);
		setAcceleration(_previousAcceleration);
		setCollisionCenter(_previousCollisionCenter);
	}

	void PhysicsEngine::accelerate(double factor, bool withRotation) {
		if(withRotation == true) {
			_acceleration = cg::Vector2d(cos(getRotation()), sin(getRotation())) * factor/_mass;
		} else {
			_acceleration = getNormalizedVelocity()  * factor/_mass;
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
			_acceleration = cg::Vector2d(cos(getRotation()), sin(getRotation())) * factor/_mass;
		} else {
			_acceleration = getNormalizedVelocity() * factor/_mass;
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
		_rotationDeg = fmod(_rotationDeg + factor/_mass, 360);
		_rotationRad = _rotationDeg * PI4 / 180;
	}

	double PhysicsEngine::getRotation() const {
		return _rotationRad;
	}
	double PhysicsEngine::getRotation(bool inDegrees) const {
		return (inDegrees == true) ? _rotationDeg : _rotationRad;
	}
	void PhysicsEngine::setRotation(double radiansRotation){
		if(_rotating == true)
			throw "cant set rotation to rotating object!";

		_rotationRad = fmod(radiansRotation, PI4);
		_rotationDeg = _rotationRad * 180/PI4;
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
		_collisionCenter = constrainVector(collisionCenter);
	}
	bool PhysicsEngine::collidesWith(PhysicsObject *pobject) {
		return (getDistance(pobject->getCollisionCenter(),getCollisionCenter()) <= pobject->getCollisionRadius() + getCollisionRadius());
	}
	
	bool PhysicsEngine::penetrates(PhysicsObject *pobject) {
		return (getDistance(pobject->getCollisionCenter(),getCollisionCenter()) < pobject->getCollisionRadius() + getCollisionRadius());
	}
	void PhysicsEngine::calculateCollision(PhysicsObject *pobject) {
		if(!collidesWith(pobject))
			return;
		
		double originalElapsedMillis = _previousElapsedMillis;
		double newElapsedMillis = _previousElapsedMillis/2;
		while( newElapsedMillis > 0.0000001 && penetrates(pobject)) {
			stepBack();
			update(newElapsedMillis);
			newElapsedMillis = _previousElapsedMillis/2;
		}

		if(penetrates(pobject)) {
			double distance = getDistance(getCollisionCenter(), pobject->getCollisionCenter());
			double factor = (pobject->getCollisionRadius() + getCollisionRadius())/(2*distance);
			
			setPosition(getPosition()-factor*normalize(constrainVector(pobject->getCollisionCenter() + getCollisionCenter())));
			setCollisionCenter(getPosition());
			pobject->setPosition(pobject->getPosition()+factor*normalize(constrainVector(pobject->getCollisionCenter() + getCollisionCenter())));
			pobject->setCollisionCenter(pobject->getPosition());
			
		}

		cg::Vector2d normalVelocity = normalize(constrainVector(getCollisionCenter() - pobject->getCollisionCenter()));
		cg::Vector2d relativeVelocity = getVelocity() - pobject->getVelocity();
		double restitutionFactor = 0.9;
		
		double j = (-(1+restitutionFactor) * dot(relativeVelocity,normalVelocity))/(dot(normalVelocity, normalVelocity)*(1/getMass() + 1/pobject->getMass()));
		setVelocity(getVelocity() + (j*normalVelocity)/getMass());
		pobject->setVelocity(pobject->getVelocity() + (-j*normalVelocity)/pobject->getMass());
	}
}

	