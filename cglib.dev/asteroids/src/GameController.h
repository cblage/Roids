#ifndef MY_CONTROLLER_H
#define MY_CONTROLLER_H

#include "cg/cg.h"
#include "SpaceShip.h"
#include "MyCamera.h"

namespace asteroids {

	class GameController : public cg::Entity,
		public cg::IKeyboardEventListener
	{
	public:
		GameController(SpaceShip* ship, MyCamera* camera);
		~GameController();
		void init();
        void onKeyPressed(unsigned char key);
        void onKeyReleased(unsigned char key);
        void onSpecialKeyPressed(int key);
        void onSpecialKeyReleased(int key);

	private:
		SpaceShip * _ship;
		MyCamera * _camera;
	};
}

#endif