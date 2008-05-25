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



namespace asteroids {
	class MyApp;

	class GameManager : public ParticleManager
	{
	private:
		int _currentScore;
		unsigned int _currentLevel, _asteroidsLeft, _shipsLeft;
		MyApp * _application;
		bool _levelRunning;

	public:
		GameManager(std::string id, MyApp *application);
		~GameManager();
		void preUpdate(unsigned long elapsed_millis);
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
	class ScreenManager;
	class ApplicationState;
	class Screen;



	class MyApp : public cg::Application {
	private:
		ApplicationState * _state;
		ScreenManager * _screenManager;
		GameManager * _gameManager;
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
