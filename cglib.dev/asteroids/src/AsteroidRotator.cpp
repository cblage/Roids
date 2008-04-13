#include "AsteroidRotator.h"

namespace asteroids {
	AsteroidRotator::AsteroidRotator(Asteroid * asteroid) : AsteroidEngine(asteroid)
	{
		_factor = 0;
		_rotating = false;
		_rotationDeg = 0;
		_rotationRad = 0;
	}
	AsteroidRotator::~AsteroidRotator() {
	}

	void AsteroidRotator::start(double factor) {
		_rotating = true;
		_factor = factor;
	}

	void AsteroidRotator::stop() {
		_rotating = false;
	}

	void AsteroidRotator::update(double elapsed_seconds) {
		if(_rotating == false) //cant be ran more often than each 0.1 seconds, nor if it's not rotating
			return;

		rotate(_factor*elapsed_seconds);
	}

	void AsteroidRotator::rotate(double factor) {
		_rotationDeg = fmod(_rotationDeg + factor, 360);
		_rotationRad = _rotationDeg * PI2 / 180;
	}

	double AsteroidRotator::getRotation() const {
		return _rotationRad;
	}
	double AsteroidRotator::getRotation(bool inDegrees) const {
		return (inDegrees == true) ? _rotationDeg : _rotationRad;
	}

}