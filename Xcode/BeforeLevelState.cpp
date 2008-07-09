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
#include "BeforeLevelState.h"

namespace asteroids {

	SINGLETON_IMPLEMENTATION(BeforeLevelState)
	
	void BeforeLevelState::enter() {
		_warmupTime = cg::Properties::instance()->getDouble("WARMUP_TIME");
		_posWarmupTime = cg::Properties::instance()->getDouble("POS_WARMUP_TIME");
		_timeLeft = _posWarmupTime+_warmupTime + cg::Properties::instance()->getDouble("PRE_WARMUP_TIME");
		_screen = new Screen("BeforeLevelScreen");
		_screen->init();
		_screen->setMessage(getMessage());
		_application->addScreen(_screen);
	}

	void BeforeLevelState::resume(MyApp * application) {
		ApplicationState * s = getPreviousState();
		changeState(application, this);
		setPreviousState(s);
		_screen->setMessage(getMessage());
		_application->addScreen(_screen);
	}
	
	void BeforeLevelState::suspend() {
		_application->removeScreen(_screen);
		//delete(_screen);
	}
	

	void BeforeLevelState::leave() {
		_application->removeScreen(_screen);
		delete(_screen);
	}

	std::string BeforeLevelState::getMessage() {
		std::ostringstream os;
		if(_timeLeft > _warmupTime+_posWarmupTime) {
			os << "Level " << _application->getGameManager()->getCurrentLevel();
			return os.str();
		} else if(_timeLeft > _posWarmupTime) {
			os << ceil(_timeLeft-_posWarmupTime);
			return os.str();
		}
		os << "Go!";
		return os.str();
	}
	
	void BeforeLevelState::update(unsigned long elapsed_millis) {
		_timeLeft -= elapsed_millis/1000.0;
		_screen->setMessage(getMessage());
		if(_timeLeft < 0) {
			DuringLevelState::instance()->changeTo(_application);
		}
	}

	std::string BeforeLevelState::getName(void) {
		return "BeforeLevelState";
	}

}
