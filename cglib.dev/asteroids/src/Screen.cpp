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
		cg::Util::instance()->drawStrokeString(_message, _winWidth/2, _winHeight/2, 0.4, true);
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