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
#include "EndOfLevelState.h"
#include "RoidsApp.h"
#include "Screen.h"
#include "BeforeLevelState.h"
#include "GameManager.h"

namespace asteroids {

	SINGLETON_IMPLEMENTATION(EndOfLevelState)
	
	void EndOfLevelState::enter() {
		_timeLeft = cg::Properties::instance()->getDouble("POS_COOLDOWN_TIME");
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
	
	void EndOfLevelState::update(unsigned long elapsed_millis) {
		_timeLeft -= elapsed_millis/1000.0;
		if(_timeLeft < 0) {
			BeforeLevelState::instance()->changeTo(_application);
		}
	}

	std::string EndOfLevelState::getName(void) {
		return "EndOfLevelState";
	}

}


