#pragma once
#ifndef EXPLOSION_MANAGER_H
#define EXPLOSION_MANAGER_H
#pragma message("ExplosionManager is included")
#include <sstream>
#include <string>
#include <vector>
#include "cg/cg.h"
#include "ParticleManager.h"
#include "ExplosionDebris.h"



namespace asteroids {
	class MyApp;

	class ExplosionManager : public ParticleManager
	{
	private:
		MyApp * _application;
		double _massDivider;

	public:
		ExplosionManager(std::string id, MyApp *application);
		~ExplosionManager();
		void createEntities();
		void generateExplosion(Particle * p);
		void createExplosionDebris(cg::Vector2d position, cg::Vector2d velocity, cg::Vector3d color = cg::Vector3d(0.7, 0.7, 0.7));
		void preDrawOverlay();
		void clearExplosions();
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
