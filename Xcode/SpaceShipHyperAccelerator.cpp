#include "SpaceShipHyperAccelerator.h"
#include "SpaceShip.h"

namespace asteroids {

	SpaceShipHyperAccelerator::SpaceShipHyperAccelerator(SpaceShip * ship) : SpaceShipEngine(ship)
	{
		_hyperAccelerating = false;
	}
	SpaceShipHyperAccelerator::~SpaceShipHyperAccelerator(void) {
	}
	void SpaceShipHyperAccelerator::update(double elapsed_seconds) {
		if(_hyperAccelerating == false)
			return;

		cg::Vector2d universeDimensions = _ship->getUniverseDimensions();
		_ship->setPosition(cg::Vector2d(randomBetween(0, universeDimensions[0]), randomBetween(0, universeDimensions[1])));
		_hyperAccelerating = false;
	}
	void SpaceShipHyperAccelerator::hyperAccelerate(void) { 
		_hyperAccelerating = true;
	}
	double SpaceShipHyperAccelerator::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}
}
