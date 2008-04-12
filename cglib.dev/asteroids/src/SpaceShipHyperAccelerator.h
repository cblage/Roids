#ifndef SPACE_SHIP_HYPERACCELERATOR_H
#define SPACE_SHIP_HYPERACCELERATOR_H

#include "cg/cg.h"
#include "SpaceShipEngine.h"

namespace asteroids {
	class SpaceShip;
	class SpaceShipHyperAccelerator : public SpaceShipEngine
	{
	public:
		SpaceShipHyperAccelerator(SpaceShip * ship);
		virtual ~SpaceShipHyperAccelerator(void);
		void update(double elapsed_seconds);
		void hyperAccelerate(void);
		double randomBetween(double min, double max);
	private:
		bool _hyperAccelerating;
	};	
}
#endif
