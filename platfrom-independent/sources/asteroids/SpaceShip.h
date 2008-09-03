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
#pragma once
#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H
#pragma message("SpaceShip is included")

#include <string>
#include <cg/cg.h>
#include <cmath>
#include <sstream>
#include <string>
#include "GameEntity.h"

namespace asteroids {
	class GameManager;
	class SpaceShipHyperAccelerator;
	class ShipController;

	class SpaceShip : public cg::IDrawListener,
		public cg::IUpdateListener, 
		public cg::IReshapeEventListener,
		public GameEntity
	{
	private:
		std::string _message;
		cg::Vector2d _size;
		double _winWidth, _winHeight, _charlesBronsonKilledSecondsAgo;		
		SpaceShipHyperAccelerator * _hyperAccelerator;
		int _charlesBronsonStyle, _maxCharlesBronsonStyle;
		ShipController * _controller;
		double _radarSize;
		int _radarAdvanced;
		double _invulTime, _invulTimeMax;
	public:
		SpaceShip(std::string id, GameManager *  gameManager);
		SpaceShip(std::string id, GameManager *  gameManager, int lifes);
		~SpaceShip();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void onReshape(int width, int height);
		void hyperAccelerate(void);
		void shootLaser(void);
		void onKeyPressed(unsigned char key);
		void onKeyReleased(unsigned char key);
		void onSpecialKeyPressed(int key);
        void onSpecialKeyReleased(int key);
		void drawOverlay();
		void dealDamage(double damage);
		double getCollisionDamage(Particle * target);
	};
}

#endif

