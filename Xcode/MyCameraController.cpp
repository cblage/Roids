/*
 Roids!
 Copyright (C) 2008 Carlos Lage, Tiago Coelho, Eduardo Castanho

 This file is part of Roids!.

 Roids! is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 Roids! is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Roids!; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "MyCameraController.h"
#include "MyCamera.h"

namespace asteroids {

	MyCameraController::MyCameraController(MyCamera* camera) : cg::Entity("MyCameraController") {
		_camera = camera;
	}
	MyCameraController::~MyCameraController() {
	}
	void MyCameraController::init() {
	}
	
	void MyCameraController::onKeyPressed(unsigned char key) {
		switch (key)
		{
			case 'j':
				_camera->startRotate(0);
				break;
			case 'l':
				_camera->startRotate(1);
				break;
			case 'i':
				_camera->startRotate(2);
				break;
			case 'k':
				_camera->startRotate(3);
				break;
			case 'u':
				_camera->startRotate(4);
				break;
		}
	}
	void MyCameraController::onKeyReleased(unsigned char key) {
		switch (key)
		{
			case 'j':
				_camera->stopRotate(0);
				break;
			case 'l':
				_camera->stopRotate(1);
				break;
			case 'i':
				_camera->stopRotate(2);
				break;
			case 'k':
				_camera->stopRotate(3);
				break;
		}
	}
	void MyCameraController::onSpecialKeyPressed(int key) {
		/*switch (key)
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
		/*switch (key)
		{
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