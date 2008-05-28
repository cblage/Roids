#pragma once
#ifndef MY_APP_H
#define MY_APP_H
#pragma message("MyApp is included")

#include "cg/cg.h"
#include "MyCamera.h"
#include "StarSphere.h"
#include "GameManager.h"
#include "Lights.h"
#include "ApplicationState.h"
#include "BeforeGameState.h"
#include "BeforeLevelState.h"
#include "ApplicationController.h"
#include "ScreenManager.h"
#include "ExplosionManager.h"

namespace asteroids {
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
}

#endif