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
#include "ShipController.h"

namespace asteroids {

	ShipController::ShipController(SpaceShip* ship) : cg::Entity("ShipController") {
		_ship = ship;
		_controlsScheme = cg::Properties::instance()->getInt("CONTROLS_SCHEME");
	}
	ShipController::~ShipController() {
	}
	void ShipController::init() {
	}
	void ShipController::onKeyPressed(unsigned char key) {
		switch(key) 
		{
			case ' ':
				_ship->shootLaser();
				break;
			case 'h':
				_ship->hyperAccelerate();
				break;
			case 'x':
				_ship->startAcceleration(-100000, false, cg::Vector2d(0, 0));
				break;
		}
		
		if(_controlsScheme != 1)
			return;
		
		switch(key) 
		{

			case  'a':
				_ship->startRotation(360);
				break;
			case 'd':
				_ship->startRotation(-360);
				break;
			case 'w':
				_ship->startAcceleration(250000, true);
				break;
			case 's':
				_ship->startAcceleration(-250000, true);
				break;
		}		

	}
	void ShipController::onKeyReleased(unsigned char key) {
		switch(key)
		{		
			case 'x':
				_ship->stopAcceleration();
				break;	
		}
		
		if(_controlsScheme != 1)
			return;
		
		switch(key) 
		{
			case 'a':
			case 'd':
				_ship->stopRotation();
				break;
			case 'w':
			case 's':
				_ship->stopAcceleration();
				break;
		}		
	}
	void ShipController::onSpecialKeyPressed(int key) {
		if(_controlsScheme != 2)
			return;
		
		switch (key)
		{
		case GLUT_KEY_LEFT:
			_ship->startRotation(360);
			break;
		case GLUT_KEY_RIGHT:
			_ship->startRotation(-360);
			break;
		case GLUT_KEY_UP:
			_ship->startAcceleration(250000, true);
			break;
		case GLUT_KEY_DOWN:
			_ship->startAcceleration(-250000, true);
			break;
		}
	}	
	void ShipController::onSpecialKeyReleased(int key) {
		if(_controlsScheme != 2)
			return;
		
		switch (key)
		{
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT:
			_ship->stopRotation();
			break;
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
			_ship->stopAcceleration();
			break;
		}
	}

}
