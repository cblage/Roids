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
#include "DuringLevelState.h"
#include "MyApp.h"
#include "GameManager.h"

namespace asteroids {

	SINGLETON_IMPLEMENTATION(DuringLevelState)
	
	void DuringLevelState::enter() {
		_application->getGameManager()->beginLevel();
	}
	void DuringLevelState::resume(MyApp * application) {
		changeState(application, this);
	}

	std::string DuringLevelState::getName(void) {
		return "DuringLevelState";
	}

}
