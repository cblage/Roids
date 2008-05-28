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

	}
	void MyCameraController::onKeyReleased(unsigned char key) {

	}
	void MyCameraController::onSpecialKeyPressed(int key) {
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
	void MyCameraController::onSpecialKeyReleased(int key) {
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