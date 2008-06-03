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
		GLboolean lightingEnabled;
		lightingEnabled = glIsEnabled(GL_LIGHTING);
		if(lightingEnabled == GL_TRUE) glDisable(GL_LIGHTING);
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
		if(lightingEnabled == GL_TRUE) glEnable(GL_LIGHTING);	
	}

}