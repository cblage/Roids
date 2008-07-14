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
#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H
#pragma message("GameEntity is included")
#include "Particle.h"
#include "../cg/cg.h"


namespace asteroids {
	class GameManager;
	
	class GameEntity : public Particle,
		public cg::IKeyboardEventListener,
		public cg::IDrawOverlayListener
	{
	private:
		GameManager * _gameManager;
		bool _destroyed;
		double _strength;
		double _penetrationTime;
		double _maxPenetrationTime;
		double _health;
		double _initHealth;
		char _particleType;
		
	public:
		GameEntity(std::string id, GameManager * GameManager, char particleType='g');
		GameEntity(std::string id, double strength, GameManager * GameManager, char particleType='g');
		GameEntity(std::string id, GameManager * GameManager, double mass, char particleType='g');
		GameEntity(std::string id, double strength, GameManager * GameManager, double mass, char particleType='g');
		virtual ~GameEntity();
		virtual GameManager * getGameManager(void);
		virtual void onKeyPressed(unsigned char key) {}
		virtual void onKeyReleased(unsigned char key) {}
		virtual void onSpecialKeyPressed(int key){}
		virtual void onSpecialKeyReleased(int key) {}
		virtual void drawOverlay() {}		
	};
}	
#endif