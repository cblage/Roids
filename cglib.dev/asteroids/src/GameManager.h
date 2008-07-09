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
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#pragma message("GameManager is included")
#include <sstream>
#include <string>
#include <vector>
#include "cg/cg.h"
#include "ParticleManager.h"
#include "ApplicationState.h"
#include "EndOfLevelState.h"
#include "GameOverState.h"
#include "ExplosionManager.h"



namespace asteroids {
	class MyApp;

	class GameManager : public ParticleManager
	{
	private:
		int _currentScore;
		unsigned int _currentLevel, _asteroidsLeft, _shipsLeft;
		MyApp * _application;
		bool _levelRunning, _cooldownPeriod;
		double _radarSize;
		double _cooldownTime, _cooldownLeft;
		double _difficulty;
		double _frameRate;
		bool _showFrameRate;
		double _frameRateAccul, _maxFrameRateAccul, _frameRateAcculDivider;

	public:
		GameManager(std::string id, MyApp *application);
		~GameManager();
		void preUpdate(unsigned long elapsed_millis);
		void postInit();
		void createEntities();
		void addParticle(Particle *p);
		void destroyParticle(std::string id);
		void createLaserShot(cg::Vector2d position, double radiansRotation, cg::Vector2d velocity, double degreesRotation);
		void resetGame();
		void beginLevel();
		void finishLevel();
		void advanceLevel();
		void changeLevel(unsigned int level);
		unsigned int getCurrentLevel();
		int getCurrentScore();
		void setScore(int score);
		void addScore(int score);
		void preDrawOverlay();
	};


#ifndef MY_APP_H
#define MY_APP_H
	class StarSphere;
	class MyCamera;
	class GameManager;
	class ExplosionManager;
	class ScreenManager;
	class ApplicationState;
	class Screen;

	class MyApp : public cg::Application {
	private:
		ApplicationState * _state;
		ScreenManager * _screenManager;
		GameManager * _gameManager;
		ExplosionManager * _explosionManager;
	public:
		MyApp();
		~MyApp();
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
