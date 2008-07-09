/*
 Roids!
 Copyright (C) 2008 Carlos Lage, Tiago Coelho, Eduardo Castanho

 This file is part of Roids!.

 Roids! is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 Roids! is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Roids!; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
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
