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
#pragma once
#ifndef APPLICATION_STATE_H
#define APPLICATION_STATE_H
#pragma message("ApplicationState is included")

#include <cg/cg.h>
#include <string>
#include <cmath>

namespace asteroids {
	class MyApp;
	class ApplicationState {
	protected:
		MyApp * _application;
		ApplicationState * _previousState;

	public:
		virtual void changeFrom();
		virtual void changeTo(MyApp * application);
		virtual void changeState(MyApp * application, ApplicationState * state);
		virtual std::string getName(void) = 0;
		virtual void onUpdate();
		virtual void onDisplay();
		virtual bool onKeyPressed(unsigned char key);
		virtual void pause();
		virtual void quit();
		virtual void enter();
		virtual void leave();
		virtual void resume(MyApp * application);
		virtual void suspend();
		virtual void setPreviousState(ApplicationState * s);
		virtual ApplicationState * getPreviousState();
		virtual void update(unsigned long elapsed_millis);
	};

}


#endif
