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
#include "GameOverScreen.h"

namespace asteroids {

	GameOverScreen::GameOverScreen(std::string id, double finalScore, unsigned int finalLevel) : Screen(id) {
		_message = "Life sucks, eh?";
		_finalScore = finalScore;
		_finalLevel = finalLevel;
		_messageY = 0.5;
	}
	GameOverScreen::~GameOverScreen() {
	}

	void GameOverScreen::drawOverlay() {
		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		//cg::Util::instance()->drawStrokeString(_message, _winWidth/2, _winHeight/2, 0.4, true, 1, 0, 0, 1);
		glPushMatrix();
		{
			glColor4d(0, 0, 0, 0.7);
			glBegin(GL_QUADS);
			{
				glVertex3d(0, 0, 0);
				glVertex3d(0, _winHeight, 0);
				glVertex3d(_winWidth, _winHeight, 0);
				glVertex3d(_winWidth, 0, 0);
			}
			glEnd();
		}
		glPopMatrix();
		

		std::ostringstream score;
		score << "Score: " << _finalScore;
		std::ostringstream level;
		level << "Level: " << _finalLevel;

		cg::Util::instance()->drawStrokeString(_message, _messageX*_winWidth, _messageY*_winHeight, 0.45, true, 2.5, 0.6, 0.1, 0.1, 1);
		cg::Util::instance()->drawStrokeString("Try again? (Y/N)", _messageX*_winWidth, _messageY*_winHeight-35, 0.2, true, 2, 0, 0.25, 0.5, 1);
		cg::Util::instance()->drawStrokeString("Stats:", _messageX*_winWidth, _messageY*_winHeight-140, 0.3, true, 2, 0.5, 0.25, 0, 1);
		cg::Util::instance()->drawStrokeString(score.str(), _messageX*_winWidth-80, _messageY*_winHeight-180, 0.2, false, 2, 0, 0.5, 0.25, 1);
		cg::Util::instance()->drawStrokeString(level.str(), _messageX*_winWidth-80, _messageY*_winHeight-220, 0.2, false, 2, 0, 0.5, 0.25, 1);
		glPopAttrib();
	}

}

