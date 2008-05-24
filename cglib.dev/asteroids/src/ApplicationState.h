#pragma once
#ifndef APPLICATION_STATE_H
#define APPLICATION_STATE_H
#pragma message("ApplicationState is included")

#include "cg/cg.h"
#include <string>
#include <cmath>

namespace asteroids {
	class MyApp;
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
	class Screen;
	class ScreenManager;


	class MyApp : public cg::Application {
	private:
		ApplicationState * _state;
		ScreenManager * _screenManager;
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
}

#endif

#endif
