#ifndef MY_CONTROLLER_H
#define MY_CONTROLLER_H

#include "cg/cg.h"
#include "SpaceShip.h"

namespace asteroids {

	class SpaceShipController : public cg::Entity,
		public cg::IKeyboardEventListener
	{
	public:
		SpaceShipController(SpaceShip* ship);
		~SpaceShipController();
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