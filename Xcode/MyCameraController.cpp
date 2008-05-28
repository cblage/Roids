#include "MyCameraController.h"

namespace asteroids {

	MyCameraController::MyCameraController(MyCamera* camera) : cg::Entity("MyCameraController") {
		_camera = camera;
	}
	MyCameraController::~MyCameraController() {
	}
	void MyCameraController::init() {
	}
	
	void MyCameraController::onKeyPressed(unsigned char key) {
  /*		if (key == 'h') {
			_ship->hyperAccelerate();
		} else if (key == 'a') {
			_ship->startRotation(540);
		} else if (key == 'd') {
			_ship->startRotation(-540);
		} else if (key == 's') {
			_ship->startAcceleration(-500000, true);
		} else if (key == 'w') {
			_ship->startAcceleration(500000, true);
		} else if (key == 'x') {
			_ship->startAcceleration(-100000, false, cg::Vector2d(0, 0));
		} else if (key == ' ') {
			_ship->shootLaser();
		}*/
	}
	void MyCameraController::onKeyReleased(unsigned char key) {
	/*	if (key == 'a') {
			_ship->stopRotation();
		} else if (key == 'd') {
			_ship->stopRotation();
		} else if (key == 's') {
			_ship->stopAcceleration();
		} else if (key == 'w') {
			_ship->stopAcceleration();
		} else if (key == 'x') {
			_ship->stopAcceleration();
		}*/
	}
	void MyCameraController::onSpecialKeyPressed(int key) {
		/*
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
		}*/
	}	
	void MyCameraController::onSpecialKeyReleased(int key) {
		/*
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
		}*/
	}

}