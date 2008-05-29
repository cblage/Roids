#include "PausedState.h"

namespace asteroids {

	SINGLETON_IMPLEMENTATION(PausedState)
	
	void PausedState::enter() {
		_screen = new Screen("PausedScreen");
		_screen->init();
		_screen->setMessage("Coffee break ^_^");
		_application->addScreen(_screen);
	}
	void PausedState::leave() {
		_application->removeScreen(_screen);
		delete(_screen);
	}

	void PausedState::changeState(MyApp * application, ApplicationState * state) {
		_application = application;
		ApplicationState * s = _application->getState();
		if(s != NULL) {
			s->suspend();
			setPreviousState(s);
		}
		_application->changeState(state);
	}

	void PausedState::onUpdate() {
		//pause the game
		_application->resetTime();
	}

	

	void PausedState::pause() {
		getPreviousState()->resume(_application);
	}

	
	std::string PausedState::getName(void) {
		return "PausedState";
	}

}
