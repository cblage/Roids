#pragma once
#ifndef BEFOREGAME_STATE_H
#define BEFOREGAME_STATE_H
#pragma message("BeforeGameState is included")

#include <string>
#include "ApplicationState.h"
#include "Screen.h"
//#include "BeforeGameScreen.h"


namespace asteroids {

	class BeforeGameState : public ApplicationState{
	SINGLETON_HEADER(BeforeGameState);
	
	private:
		Screen * _screen;

	public:
		void onKeyPressed(unsigned char key);
		void pause();
		void enter();
		void leave();
		std::string getName(void);
	};

}

#endif
