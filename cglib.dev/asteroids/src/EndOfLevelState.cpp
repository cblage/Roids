#include "EndOfLevelState.h"

namespace asteroids {

	SINGLETON_IMPLEMENTATION(EndOfLevelState)
	
	void EndOfLevelState::enter() {
		_screen = new Screen("EndOfLevelScreen");
		_screen->init();
		std::ostringstream os;
		os << "Level " << _application->getGameManager()->getCurrentLevel() << " cleared!";
		_screen->setMessage(os.str());
		_application->addScreen(_screen);
	}
	
	void EndOfLevelState::leave() {
		_application->removeScreen(_screen);
		delete(_screen);
		_application->getGameManager()->advanceLevel();
	}

	void EndOfLevelState::suspend() {
		_application->removeScreen(_screen);
		delete(_screen);
	}

	bool EndOfLevelState::onKeyPressed(unsigned char key) {
		if(!ApplicationState::onKeyPressed(key) && key == 13) {
			BeforeLevelState::instance()->changeTo(_application);
			return true;
		}
		return false;
	}
	
	void EndOfLevelState::pause() {
		
	}

	void EndOfLevelState::onUpdate() {
		_application->resetTime();
	}

	std::string EndOfLevelState::getName(void) {
		return "EndOfLevelState";
	}

}
