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
#include "BeforeGameState.h"
#include "MyApp.h"
#include "BeforeLevelState.h"
#include "Screen.h"
#include "GameManager.h"

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
		_application->getGameManager()->changeLevel(cg::Properties::instance()->getInt("INITIAL_LEVEL"));
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
		BeforeLevelState::instance()->changeTo(_application);
	}
	
	std::string BeforeGameState::getName(void) {
		return "BeforeGameState";
	}

}


