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
#ifndef EXPLOSION_MANAGER_H
#define EXPLOSION_MANAGER_H
#pragma message("ExplosionManager is included")
#include <sstream>
#include <string>
#include <vector>
#include <cg/cg.h>
#include "ParticleManager.h"


namespace asteroids {
	class RoidsApp;

	class ExplosionManager : public ParticleManager
	{
	private:
		RoidsApp * _application;
		double _massDivider;

	public:
		ExplosionManager(std::string id, RoidsApp *application);
		~ExplosionManager();
		void createEntities();
		void generateExplosion(Particle * p);
		void createExplosionDebris(cg::Vector2d position, cg::Vector2d velocity, cg::Vector3d color = cg::Vector3d(0.7, 0.7, 0.7));
		void preDrawOverlay();
		void clearExplosions();
	};


#ifndef ROIDS_APP_H
#define ROIDS_APP_H
	class StarSphere;
	class Camera;
	class GameManager;
	class ExplosionManager;
	class ScreenManager;
	class ApplicationState;
	class Screen;

	class RoidsApp : public cg::Application {
	private:
		ApplicationState * _state;
		ScreenManager * _screenManager;
		GameManager * _gameManager;
		ExplosionManager * _explosionManager;
	public:
		RoidsApp();
		~RoidsApp();
		void createEntities();
		void onUpdate();
		void onDisplay();
		void changeState(ApplicationState * state);
		ApplicationState * getState();
		void onKeyPressed(unsigned char key);
		void pause();
		void quit();
		GameManager * getGameManager();
		ExplosionManager * getExplosionManager();
		void addScreen(Screen * s);
		void removeScreen(Screen * s);
		void resetTime();

	};

#endif

}

#endif


