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
		double _timeLeft, _warmupTime, _posWarmupTime;

	public:
		void enter();
		void suspend();
		void resume(MyApp * application);
		void leave();
		std::string getName(void);
		std::string getMessage() ;
		void update(unsigned long elapsed_millis);
	};

}

#endif
