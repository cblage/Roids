#pragma once
#ifndef BEFORELEVEL_STATE_H
#define BEFORELEVEL_STATE_H
#pragma message("BeforeLevelState is included")

#include <string>
#include "ApplicationState.h"
#include "Screen.h"
#include "DuringLevelState.h"


namespace asteroids {

	class BeforeLevelState : public ApplicationState{
	SINGLETON_HEADER(BeforeLevelState);
	
	private:
		Screen * _screen;

	public:
		bool onKeyPressed(unsigned char key);
		void enter();
		void leave();
		std::string getName(void);
	};

}

#endif
