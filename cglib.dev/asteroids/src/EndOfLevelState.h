#pragma once
#ifndef ENDOFLEVEL_STATE_H
#define ENDOFLEVEL_STATE_H
#pragma message("EndOfLevelState is included")

#include <string>
#include "ApplicationState.h"
#include "Screen.h"
#include "BeforeLevelState.h"


namespace asteroids {

	class EndOfLevelState : public ApplicationState{
	SINGLETON_HEADER(EndOfLevelState);
	
	private:
		Screen * _screen;

	public:
		bool onKeyPressed(unsigned char key);
		void enter();
		void leave();
		void suspend();
		void onUpdate();
		std::string getName(void);
		void pause();
	};

}

#endif
