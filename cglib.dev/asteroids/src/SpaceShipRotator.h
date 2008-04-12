#ifndef SPACE_SHIP_ROTATOR_H
#define SPACE_SHIP_ROTATOR_H

#include "cg/cg.h"
#include "SpaceShipEngine.h"

namespace asteroids {
	class SpaceShip;
	const double PI  = 4.0*atan(1.0);
	class SpaceShipRotator : public SpaceShipEngine
	{
	public:
		SpaceShipRotator(SpaceShip * ship);
		virtual ~SpaceShipRotator(void);
		void start(double factor);
		void stop();
		void update(double elapsed_seconds);
		double getRotation() const;
		double getRotation(bool inDegrees) const;
		void rotate(double factor);
		
	private: 
		double _factor, _rotationDeg, _rotationRad;
		bool _rotating;
	};
}
#endif
