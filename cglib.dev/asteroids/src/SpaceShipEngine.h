#ifndef SPACE_SHIP_ENGINE_H
#define SPACE_SHIP_ENGINE_H

#include "cg/cg.h"

namespace asteroids {
	class SpaceShip;
	
	class SpaceShipEngine
	{
	public:
		SpaceShipEngine(SpaceShip * ship) : _ship(ship) {}
		~SpaceShipEngine(void) {}
		virtual void update(double elapsed_seconds) = 0;

	protected:
		SpaceShip * _ship;
	};
}

#endif