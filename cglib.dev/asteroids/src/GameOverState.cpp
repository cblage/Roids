#include "GameOverState.h"

namespace asteroids {

	SINGLETON_IMPLEMENTATION(GameOverState)
	
	void GameOverState::enter() {
		_screen = new GameOverScreen("GameOverScreen", _application->getGameManager()->getCurrentScore(), _application->getGameManager()->getCurrentLevel());
		_screen->init();
		_application->addScreen(_screen);
	}
	void GameOverState::leave() {
		_application->removeScreen(_screen);
		delete(_screen);
		_application->getGameManager()->resetGame();
		_application->getGameManager()->beginLevel();
	}

	void GameOverState::suspend() {
		_application->removeScreen(_screen);
		delete(_screen);
	}

	void GameOverState::onUpdate() {
		//pause the game
		_application->resetTime();
	}

	bool GameOverState::onKeyPressed(unsigned char key) {
		if(key == 'y') {
			BeforeGameState::instance()->changeTo(_application);
			return true;
		} else if(key =='n' || key == 27) {
			_application->quit();
			return true;
		}
		return false;
	}
	

	void GameOverState::pause() {
	}

	
	std::string GameOverState::getName(void) {
		return "GameOverState";
	}

}
