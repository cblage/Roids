#include "BeforeGameState.h"

namespace asteroids {

	SINGLETON_IMPLEMENTATION(BeforeGameState)
	
	void BeforeGameState::enter() {
		_screen = new Screen("BeforeGameScreen");
		_screen->init();
		_screen->setMessage("Press any key to start!");
		_application->addScreen(_screen);
	}
	void BeforeGameState::leave() {
		_application->removeScreen(_screen);
		delete(_screen);
		_application->getGameManager()->resetGame();
		_application->getGameManager()->changeLevel(1);
	}


	void BeforeGameState::suspend() {
		_application->removeScreen(_screen);
		delete(_screen);
	}

	bool BeforeGameState::onKeyPressed(unsigned char key) {
		if(!ApplicationState::onKeyPressed(key)) {
			BeforeLevelState::instance()->changeTo(_application);
			return true;
		}
		return false;
	}
	

	void BeforeGameState::pause() {
	}
	
	std::string BeforeGameState::getName(void) {
		return "BeforeGameState";
	}

}
