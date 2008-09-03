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
#include "SpaceShipController.h"
#include "SpaceShip.h"

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
			_ship->startAcceleration(-500, true);
		} else if (key == 'w') {
			_ship->startAcceleration(500, true);
		} else if (key == 'x') {
			_ship->startAcceleration(-1000, false, cg::Vector2d(0, 0));
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

