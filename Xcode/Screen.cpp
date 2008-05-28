#include "Screen.h"

namespace asteroids {

	Screen::Screen(std::string id) : Entity(id) {
		_message = "undefined message";
		_messageX = 0.5;
		_messageY = 0.5;
	}
	Screen::~Screen() {
	}

	void Screen::init() {
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
	}
	
	void Screen::drawOverlay() {
		GLboolean lightingEnabled;
		lightingEnabled = glIsEnabled(GL_LIGHTING);
		if(lightingEnabled == GL_TRUE) glDisable(GL_LIGHTING);
		//cg::Util::instance()->drawStrokeString(_message, _winWidth/2, _winHeight/2, 0.4, true, 1, 0, 0, 1);
		glPushMatrix();
		{
			glColor4d(0, 0, 0, 0.9);
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
		
		//cg::Util::instance()->drawStrokeString(_message, _winWidth/2, _winHeight/2, 0.4, true, 2, 0, 0.5, 0, 1);
		cg::Util::instance()->drawStrokeString(_message, _messageX*_winWidth, _messageY*_winHeight, 0.4, true, 2, 0, 0.25, 0.5, 1);
		if(lightingEnabled == GL_TRUE) glEnable(GL_LIGHTING);	
	}
	
	void Screen::draw() {
		
	}

	void Screen::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}

	std::string Screen::getMessage() {
		return _message;
	}

	void Screen::setMessage(std::string message) {
		_message = message;
	}

	cg::Vector2d Screen::getMessagePosition() {
		return cg::Vector2d(_messageX, _messageY);
	}

	void Screen::setMessagePosition(double x, double y) {
		if(x > 1 || x < 0) {
			throw "message position X out of bounds";
		}
		if(y > 1 || y < 0) {
			throw "message position Y out of bounds";
		}
		_messageX = x;
		_messageY = y;
	}
}