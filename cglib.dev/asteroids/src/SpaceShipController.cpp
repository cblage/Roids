#include "SpaceShipController.h"

namespace asteroids {

	SpaceShipController::SpaceShipController(SpaceShip* ship) : cg::Entity("Controller") {
		_ship = ship;
	}
	SpaceShipController::~SpaceShipController() {
	}
	void SpaceShipController::init() {
	}
	void SpaceShipController::onKeyPressed(unsigned char key) {
        if (key == 27) {
			cg::Manager::instance()->shutdownApp();
			//change this to pause later
        } else if (key == ' ') {
			_ship->hyperAccelerate();
        } else if (key == 'a') {
			_ship->startRotation(540);
		} else if (key == 'd') {
			_ship->startRotation(-540);
		} else if (key == 's') {
			_ship->startAcceleration(-15, true);
		} else if (key == 'w') {
			_ship->startAcceleration(15, true);
		} else if (key == 'x') {
			_ship->startAcceleration(-50, false, cg::Vector2d(0, 0));
		}
	}
	void SpaceShipController::onKeyReleased(unsigned char key) {
		if (key == 'a') {
			_ship->stopRotation();
		} else if (key == 'd') {
			_ship->stopRotation();
		} else if (key == 's') {
			_ship->stopAcceleration();
		} else if (key == 'w') {
			_ship->stopAcceleration();
		} else if (key == 'x') {
			_ship->stopAcceleration();
		}
	}
	void SpaceShipController::onSpecialKeyPressed(int key) {
	}
	void SpaceShipController::onSpecialKeyReleased(int key) {
        if (key == GLUT_KEY_F1) {
			cg::Manager::instance()->getApp()->dump();
        }
	}

}