#pragma once
#ifndef QUITCONFIRM_STATE_H
#define QUITCONFIRM_STATE_H
#pragma message("QuitConfirmState is included")

#include <string>
#include "ApplicationState.h"
#include "Screen.h"



namespace asteroids {

	class QuitConfirmState : public ApplicationState{
	SINGLETON_HEADER(QuitConfirmState);
	
	private:
		Screen * _screen;

	public:
		void changeState(MyApp * application, ApplicationState * state);
		bool onKeyPressed(unsigned char key);
		void onUpdate();
		void pause();
		void quit();
		void enter();
		void leave();
		std::string getName(void);
	};

}

#endif
