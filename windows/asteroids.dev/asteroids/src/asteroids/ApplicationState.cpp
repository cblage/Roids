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
#include "ApplicationState.h"
#include "GameManager.h"
#include "MyApp.h"
#include "QuitConfirmState.h"
#include "PausedState.h"


namespace asteroids {

	void ApplicationState::changeFrom() {
		leave();
	}
	void ApplicationState::changeTo(MyApp * application) {
		changeState(application, this);
		enter();
	}
	void ApplicationState::changeState(MyApp * application, ApplicationState * state) {
		_application = application;
		ApplicationState * s = _application->getState();
		if(s != NULL) {
			s->changeFrom();
			setPreviousState(s);
		}
		_application->changeState(state);
	}
	void ApplicationState::onDisplay() {
		_application->cg::Application::onDisplay();
	}
	void ApplicationState::onUpdate() {
		_application->cg::Application::onUpdate();
	}
	bool ApplicationState::onKeyPressed(unsigned char key) {
		switch(key) {
			case 'p':
			case 'P':
				_application->pause();
				return true;
			case 27:
				_application->quit();
				return true;
			default:
				return false;
		}
	}

	void ApplicationState::resume(MyApp *application) {
		ApplicationState * s = getPreviousState();
		changeTo(application);
		setPreviousState(s);
	}
	void ApplicationState::suspend() {
		changeFrom();
	}
	void ApplicationState::enter() {
	
	}
	void ApplicationState::leave() {
	}

	void ApplicationState::pause() {
		PausedState::instance()->changeTo(_application);
	}
	void ApplicationState::quit() {
		QuitConfirmState::instance()->changeTo(_application);
	}
	
	void ApplicationState::setPreviousState(ApplicationState * s) {
		_previousState = s;
	}

	ApplicationState * ApplicationState::getPreviousState() {
		return _previousState;
	}

	void ApplicationState::update(unsigned long elapsed_millis) {
	
	}
}
