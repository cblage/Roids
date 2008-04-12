#include "SpaceShipRotator.h"

namespace asteroids {
	SpaceShipRotator::SpaceShipRotator(SpaceShip * ship) : SpaceShipEngine(ship)
	{
		_factor = 0;
		_rotating = false;
		_rotationDeg = 0;
		_rotationRad = 0;
	}
	SpaceShipRotator::~SpaceShipRotator() {
	}

	void SpaceShipRotator::start(double factor) {
		_rotating = true;
		_factor = factor;
	}

	void SpaceShipRotator::stop() {
		_rotating = false;
	}

	void SpaceShipRotator::update(double elapsed_seconds) {
		if(_rotating == false) //cant be ran more often than each 0.1 seconds, nor if it's not rotating
			return;

		rotate(_factor*elapsed_seconds);
	}

	void SpaceShipRotator::rotate(double factor) {
		_rotationDeg = _rotationDeg + factor;
		if(_rotationDeg > 360) {
			_rotationDeg = 360 - _rotationDeg;
		} else if(_rotationDeg < 0) {
			_rotationDeg = 360 + _rotationDeg;
		}
		_rotationRad = _rotationDeg * PI / 180;
	}

	double SpaceShipRotator::getRotation() const {
		return _rotationRad;
	}
	double SpaceShipRotator::getRotation(bool inDegrees) const {
		return (inDegrees == true) ? _rotationDeg : _rotationRad;
	}

}