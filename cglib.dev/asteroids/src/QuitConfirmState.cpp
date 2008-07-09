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
#include "QuitConfirmState.h"

namespace asteroids {

	SINGLETON_IMPLEMENTATION(QuitConfirmState)
	
	void QuitConfirmState::enter() {
		_screen = new Screen("QuitConfirmScreen");
		_screen->init();
		_screen->setMessage("Leaving already? (Y/N)");
		_application->addScreen(_screen);
	}
	void QuitConfirmState::leave() {
		_application->removeScreen(_screen);
		delete(_screen);
	}

	void QuitConfirmState::changeState(MyApp * application, ApplicationState * state) {
		_application = application;
		ApplicationState * s = _application->getState();
		if(s != NULL) {
			s->suspend();
			setPreviousState(s);
		}
		_application->changeState(state);
	}

	void QuitConfirmState::onUpdate() {
		//pause the game
		_application->resetTime();
	}

	bool QuitConfirmState::onKeyPressed(unsigned char key) {
		if(key == 'y') {
			 cg::Manager::instance()->shutdownApp();
			 return true;
		} else if(key =='n') {
			getPreviousState()->resume(_application);
			return true;
		}
		return false;
	}
	

	void QuitConfirmState::pause() {
	}

	void QuitConfirmState::quit() {
	}
	
	std::string QuitConfirmState::getName(void) {
		return "QuitConfirmState";
	}

}
