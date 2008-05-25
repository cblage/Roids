#include "BeforeLevelState.h"

namespace asteroids {

	SINGLETON_IMPLEMENTATION(BeforeLevelState)
	
	void BeforeLevelState::enter() {
		_screen = new Screen("BeforeLevelScreen");
		_screen->init();
		std::ostringstream os;
		os << "Level " << _application->getGameManager()->getCurrentLevel();
		_screen->setMessage(os.str());
		_application->addScreen(_screen);
	}
	
	void BeforeLevelState::leave() {
		_application->removeScreen(_screen);
		delete(_screen);
	}

	bool BeforeLevelState::onKeyPressed(unsigned char key) {
		if(!ApplicationState::onKeyPressed(key)) {
			DuringLevelState::instance()->changeTo(_application);
			return true;
		}
		return false;
	}
	
	void BeforeLevelState::pause() {
		
	}

	std::string BeforeLevelState::getName(void) {
		return "BeforeLevelState";
	}

}
