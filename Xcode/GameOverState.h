#pragma once
#ifndef GAMEOVER_STATE_H
#define GAMEOVER_STATE_H
#pragma message("GameOverState is included")

#include <string>
#include "ApplicationState.h"
#include "GameOverScreen.h"
#include "BeforeGameState.h"



namespace asteroids {

	class GameOverState : public ApplicationState{
	SINGLETON_HEADER(GameOverState);
	
	private:
		Screen * _screen;

	public:
		bool onKeyPressed(unsigned char key);
		void onUpdate();
		void pause();
		void suspend();
		void enter();
		void leave();
		std::string getName(void);
	};

}

#endif
