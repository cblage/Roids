#include "AsteroidAccelerator.h"
#include "Asteroid.h"

namespace asteroids {
	AsteroidAccelerator::AsteroidAccelerator(Asteroid * asteroid) : AsteroidEngine(asteroid)
	{
		_factor = 0;
		_withMinVelocity = false;
		_withRotation = false;
		_minVelocity = cg::Vector2d(0, 0);
		_accelerating = false;
		_acceleration = cg::Vector2d(0, 0);
	}
	
	AsteroidAccelerator::~AsteroidAccelerator() {
	}

	void AsteroidAccelerator::start(double factor, bool withRotation) {
		_accelerating = true;
		_factor = factor;
		_withMinVelocity = false;
		_withRotation = withRotation;		
	}

	void AsteroidAccelerator::start(double factor, bool withRotation, cg::Vector2d minVelocity) {
		_factor = factor;
		_withMinVelocity = true;
		_minVelocity = minVelocity;
		_withRotation = withRotation;
		_accelerating = true;
	}

	void AsteroidAccelerator::stop() {
		_accelerating = false;
	}

	void AsteroidAccelerator::update(double elapsed_seconds) {
		if(_accelerating == true) {
			if(_withMinVelocity == true) {
				accelerate(_factor, _withRotation, _minVelocity);
			} else {
				accelerate(_factor, _withRotation);
			}
		}
	}

	void AsteroidAccelerator::accelerate(double factor, bool withRotation) {
		if(withRotation == true) {
			_acceleration = cg::Vector2d(cos(_asteroid->getRotation()), sin(_asteroid->getRotation())) * factor;
		} else {
			_acceleration = _asteroid->getNormalizedVelocity()  * factor;
		}

		cg::Vector2d newVelocity = _asteroid->getVelocity() + _acceleration;
		if(abs(newVelocity[0]) < 1) {
			newVelocity[0] = 0;
			_acceleration[0] = 0;
		} 
		if(abs(newVelocity[1]) < 1) {
			newVelocity[1] = 0;
			_acceleration[1] = 0;
		} 		
		_asteroid->setVelocity(newVelocity);
	}

	void AsteroidAccelerator::accelerate(double factor, bool withRotation, cg::Vector2d minVelocity) {
		if(withRotation == true) {
			_acceleration = cg::Vector2d(cos(_asteroid->getRotation()), sin(_asteroid->getRotation())) * factor;
		} else {
			_acceleration = _asteroid->getNormalizedVelocity() * factor;
		}
		cg::Vector2d newVelocity = _asteroid->getVelocity() + _acceleration;
		if(abs(newVelocity[0]) < minVelocity[0] || abs(newVelocity[0]) < 5) {
			newVelocity[0] = 0;
			_acceleration[0] = 0;
		} 
		if(abs(newVelocity[1]) < minVelocity[1] || abs(newVelocity[1]) < 5) {
			newVelocity[1] = 0;
			_acceleration[1] = 0;
		} 		

		_asteroid->setVelocity(newVelocity);
	}

	cg::Vector2d AsteroidAccelerator::getAcceleration() const {
		return _acceleration;
	}
}