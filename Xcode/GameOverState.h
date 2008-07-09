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
#ifndef GAMEOVER_STATE_H
#define GAMEOVER_STATE_H
#pragma message("GameOverState is included")

#include <string>
#include "ApplicationState.h"
#include "GameOverScreen.h"
#include "BeforeGameState.h"



namespace asteroids {

	class GameOverState : public ApplicationState{
	SINGLETON_HEADER(GameOverState);
	
	private:
		Screen * _screen;

	public:
		bool onKeyPressed(unsigned char key);
		void onUpdate();
		void pause();
		void suspend();
		void enter();
		void leave();
		std::string getName(void);
	};

}

#endif
