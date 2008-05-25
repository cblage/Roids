#include "QuitConfirmState.h"

namespace asteroids {

	SINGLETON_IMPLEMENTATION(QuitConfirmState)
	
	void QuitConfirmState::enter() {
		_screen = new Screen("QuitConfirmScreen");
		_screen->init();
		_screen->setMessage("Leaving already? (Y/N)");
		_application->addScreen(_screen);
	}
	void QuitConfirmState::leave() {
		_application->removeScreen(_screen);
		delete(_screen);
	}

	void QuitConfirmState::changeState(MyApp * application, ApplicationState * state) {
		_application = application;
		ApplicationState * s = _application->getState();
		if(s != NULL) {
			s->suspend();
			setPreviousState(s);
		}
		_application->changeState(state);
	}

	void QuitConfirmState::onUpdate() {
		//pause the game
		_application->resetTime();
	}

	bool QuitConfirmState::onKeyPressed(unsigned char key) {
		if(key == 'y') {
			 cg::Manager::instance()->shutdownApp();
			 return true;
		} else if(key =='n') {
			getPreviousState()->resume(_application);
			return true;
		}
		return false;
	}
	

	void QuitConfirmState::pause() {
	}

	void QuitConfirmState::quit() {
	}
	
	std::string QuitConfirmState::getName(void) {
		return "QuitConfirmState";
	}

}
