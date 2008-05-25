#pragma once
#ifndef PAUSED_STATE_H
#define PAUSED_STATE_H
#pragma message("PausedState is included")

#include <string>
#include "ApplicationState.h"
#include "Screen.h"



namespace asteroids {

	class PausedState : public ApplicationState{
	SINGLETON_HEADER(PausedState);
	
	private:
		Screen * _screen;

	public:
		void changeState(MyApp * application, ApplicationState * state);
		void onUpdate();
		void pause();
		void enter();
		void leave();
		std::string getName(void);
	};

}

#endif
