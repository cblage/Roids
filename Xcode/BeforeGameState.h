#pragma once
#ifndef BEFOREGAME_STATE_H
#define BEFOREGAME_STATE_H
#pragma message("BeforeGameState is included")

#include <string>
#include "ApplicationState.h"
#include "BeforeLevelState.h"
#include "Screen.h"



namespace asteroids {

	class BeforeGameState : public ApplicationState{
	SINGLETON_HEADER(BeforeGameState);
	
	private:
		Screen * _screen;

	public:
		void suspend();
		bool onKeyPressed(unsigned char key);
		void pause();
		void enter();
		void leave();
		std::string getName(void);
	};

}

#endif
