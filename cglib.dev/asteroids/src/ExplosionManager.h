#pragma once
#ifndef EXPLOSION_MANAGER_H
#define EXPLOSION_MANAGER_H
#pragma message("ExplosionManager is included")
#include <sstream>
#include <string>
#include <vector>
#include "cg/cg.h"
#include "ParticleManager.h"




namespace asteroids {
	class MyApp;

	class ExplosionManager : public ParticleManager
	{
	private:
		MyApp * _application;

	public:
		ExplosionManager(std::string id, MyApp *application);
		~ExplosionManager();
		void createEntities();
		void generateExplosion(Particle * p);
		void createExplosionDebris(cg::Vector2d position, cg::Vector2d velocity);
		void createExplosionCenter(cg::Vector2d position, cg::Vector2d velocity);
		void preDrawOverlay();
	};


#ifndef MY_APP_H
#define MY_APP_H
	class StarSphere;
	class MyCamera;
	class ExplosionManager;
	class ScreenManager;
	class ApplicationState;
	class Screen;



	class MyApp : public cg::Application {
	private:
		ApplicationState * _state;
		ScreenManager * _screenManager;
		ExplosionManager * _gameManager;
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
		void addScreen(Screen * s);
		void removeScreen(Screen * s);
	};
#endif

}

#endif
