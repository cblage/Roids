#pragma once
#ifndef SHIP_CONTROLLER_H
#define SHIP_CONTROLLER_H
#pragma message("ShipController is included")

#include "cg/cg.h"
#include "SpaceShip.h"

namespace asteroids {
	class SpaceShip;

	class ShipController : public cg::Entity,
		public cg::IKeyboardEventListener
	{
	public:
		ShipController(SpaceShip* ship);
		~ShipController();
		void init();
        void onKeyPressed(unsigned char key);
        void onKeyReleased(unsigned char key);
        void onSpecialKeyPressed(int key);
        void onSpecialKeyReleased(int key);

	private:
		SpaceShip * _ship;
	};


}

#endif