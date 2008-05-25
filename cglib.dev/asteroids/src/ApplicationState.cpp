#include "ApplicationState.h"

namespace asteroids {

	void ApplicationState::changeFrom() {
		leave();
	}
	void ApplicationState::changeTo(MyApp * application) {
		changeState(application, this);
		enter();
	}
	void ApplicationState::changeState(MyApp * application, ApplicationState * state) {
		_application = application;
		ApplicationState * s = _application->getState();
		if(s != NULL) {
			s->changeFrom();
			setPreviousState(s);
		}
		_application->changeState(state);
	}
	void ApplicationState::onDisplay() {
		_application->cg::Application::onDisplay();
	}
	void ApplicationState::onUpdate() {
		_application->cg::Application::onUpdate();
	}
	bool ApplicationState::onKeyPressed(unsigned char key) {
		switch(key) {
			case 'p':
			case 'P':
				_application->pause();
				return true;
			case 27:
				_application->quit();
				return true;
			default:
				return false;
		}
	}

	void ApplicationState::resume(MyApp *application) {
		changeTo(application);
	}
	void ApplicationState::suspend() {
		changeFrom();
	}
	void ApplicationState::enter() {
	
	}
	void ApplicationState::leave() {
	}

	void ApplicationState::pause() {
		//PausedState::instance()->changeTo(_application);
	}
	void ApplicationState::quit() {
		QuitConfirmState::instance()->changeTo(_application);
	}
	
	void ApplicationState::setPreviousState(ApplicationState * s) {
		_previousState = s;
	}

	ApplicationState * ApplicationState::getPreviousState() {
		return _previousState;
	}
}
