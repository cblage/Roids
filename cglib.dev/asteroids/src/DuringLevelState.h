#pragma once
#ifndef DURINGLEVEL_STATE_H
#define DURINGLEVEL_STATE_H
#pragma message("DuringLevelState is included")

#include <string>
#include "ApplicationState.h"



namespace asteroids {

	class DuringLevelState : public ApplicationState{
	SINGLETON_HEADER(DuringLevelState);

	public:
		void enter();
		std::string getName(void);
	};

}

#endif
