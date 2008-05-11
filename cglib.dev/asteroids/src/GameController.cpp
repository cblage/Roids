#include "GameController.h"

namespace asteroids {

	GameController::GameController(SpaceShip* ship, MyCamera* camera) : cg::Entity("Controller") {
		_ship = ship;
		_camera = camera;
	}
	GameController::~GameController() {
	}
	void GameController::init() {
	}
	void GameController::onKeyPressed(unsigned char key) {
        if (key == 27) {
			cg::Manager::instance()->shutdownApp();
			//change this to pause later
        } else if (key == 'h') {
			_ship->hyperAccelerate();
        } else if (key == 'a') {
			_ship->startRotation(540);
		} else if (key == 'd') {
			_ship->startRotation(-540);
		} else if (key == 's') {
			_ship->startAcceleration(-500, true);
		} else if (key == 'w') {
			_ship->startAcceleration(500, true);
		} else if (key == 'x') {
			_ship->startAcceleration(-1000, false, cg::Vector2d(0, 0));
		} else if (key == ' ') {
			_ship->shootLaser();
		}
	}
	void GameController::onKeyReleased(unsigned char key) {
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
	void GameController::onSpecialKeyPressed(int key) {
		switch (key)
		{
		case GLUT_KEY_LEFT:
			_camera->startRotate(0);
			break;
		case GLUT_KEY_RIGHT:
			_camera->startRotate(1);
			break;
		case GLUT_KEY_UP:
			_camera->startRotate(2);
			break;
		case GLUT_KEY_DOWN:
			_camera->startRotate(3);
			break;
		case GLUT_KEY_HOME:
			_camera->startRotate(4);
			break;
		default:
			return;
		}
	}	
	void GameController::onSpecialKeyReleased(int key) {
		switch (key)
		{
		case GLUT_KEY_F1:
			cg::Manager::instance()->getApp()->dump();
			break;
		case GLUT_KEY_LEFT:
			_camera->stopRotate(0);
			break;
		case GLUT_KEY_RIGHT:
			_camera->stopRotate(1);
			break;
		case GLUT_KEY_UP:
			_camera->stopRotate(2);
			break;
		case GLUT_KEY_DOWN:
			_camera->stopRotate(3);
			break;
		default:
			return;
		}
	}

}
