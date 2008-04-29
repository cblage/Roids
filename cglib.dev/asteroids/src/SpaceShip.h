#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H

#include <string>
#include "cg/cg.h"
#include <cmath>
#include "SpaceShipAccelerator.h"
#include "SpaceShipRotator.h"
#include "SpaceShipHyperAccelerator.h"
#include "PhysicsObject.h"

namespace asteroids {
	class SpaceShip : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener,
		public cg::IDrawOverlayListener,
		public PhysicsObject
	{
	private:
		cg::Vector2d _size;
		double _winWidth, _winHeight;		
		SpaceShipHyperAccelerator * _hyperAccelerator;

	public:
		SpaceShip(std::string id);
		~SpaceShip();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void drawOverlay();
        void onReshape(int width, int height);
		void hyperAccelerate(void);
	};
}

#endif