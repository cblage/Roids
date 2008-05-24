#include "Screen.h"

namespace asteroids {

	Screen::Screen(std::string id) : Entity(id) {
	
	}
	Screen::~Screen() {
	}

	void Screen::init() {
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
	}
	
	void Screen::drawOverlay() {
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
		
		cg::Util::instance()->drawStrokeString(_message, _winWidth/2, _winHeight/2, 0.4, true, 4, 1, 1, 1, 1);
		cg::Util::instance()->drawStrokeString(_message, _winWidth/2, _winHeight/2, 0.4, true, 2, 0, 1, 0, 1);

		GLfloat ambientLight[] = { 1, 1, 1, 1.0 };
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	
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
}