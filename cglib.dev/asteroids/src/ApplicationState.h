#pragma once
#ifndef APPLICATION_STATE_H
#define APPLICATION_STATE_H
#pragma message("ApplicationState is included")

#include "cg/cg.h"
#include <string>
#include <cmath>

namespace asteroids {
	class MyApp;
	class GameManager;
	class ApplicationState {
	protected:
		MyApp * _application;

	public:
		void changeFrom();
		void changeTo(MyApp * application);
		void changeState(MyApp * application, ApplicationState * state);
		virtual std::string getName(void) = 0;
		virtual void onUpdate();
		virtual void onDisplay();
		virtual void onKeyPressed(unsigned char key);
		virtual void pause();
		virtual void quit();
		virtual void enter();
		virtual void leave();
	};

}

#ifndef MY_APP_H
#define MY_APP_H

namespace asteroids {
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
		GameManager * getGameManager();
		void addScreen(Screen * s);
		void removeScreen(Screen * s);

	};
}

#endif
namespace asteroids {

#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H
	class Asteroid;
	class LaserShot;
	class Particle;

	class ParticleManager : public cg::Group,
		public cg::GroupDraw,
		public cg::GroupUpdate,
		public cg::GroupKeyboardEvent,
		public cg::GroupReshapeEvent,
		public cg::GroupDrawOverlay
	{
	protected:
		std::string _numParticlesMessage;
		std::vector<std::string> _deletedParticles;
		std::vector<Particle *> _newParticles;

		unsigned int _currIdNum;

		virtual void createEntities();
		virtual void postInit();
	public:
		ParticleManager(std::string id);
		~ParticleManager();
		virtual void destroyParticle(std::string id);
		virtual void preUpdate(unsigned long elapsed_millis);
		virtual void postUpdate(unsigned long elapsed_millis);
		virtual void createAsteroids(unsigned int numAsteroids, double scaleFactor, double radius, cg::Vector2d position);
		virtual void createAsteroids(unsigned int numAsteroids, double scaleFactor);
		virtual void createAsteroids(unsigned int numAsteroids);
		virtual void createAsteroid(double scaleFactor, cg::Vector2d position);
		virtual void createAsteroid(double scaleFactor, cg::Vector2d position, cg::Vector2d velocity);
		virtual void createAsteroid(cg::Vector2d position);
		virtual void createAsteroid(void);
		virtual void createLaserShot(cg::Vector2d position, double radiansRotation, cg::Vector2d velocity, double degreesRotation);
		virtual void createShip(cg::Vector2d position, double radiansRotation, cg::Vector2d velocity, double degreesRotation);
		virtual void createShip(void);
		virtual void preDrawOverlay();
		virtual double randomBetween(double min, double max);
		virtual std::vector<Particle*> getParticles();
		virtual void addParticle(Particle * p);
		virtual Particle * getParticle(std::string id);
	};


#endif
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

	class MyApp;
	class Particle;

	class GameManager : public ParticleManager
	{
	private:
		int _currentScore;
		unsigned int _currentLevel, _asteroidsLeft, _shipsLeft;
		MyApp * _application;

	public:
		GameManager(std::string id, MyApp *application);
		~GameManager();
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
#endif
}
#endif
