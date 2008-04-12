#include "MyCamera.h"

namespace asteroids {

    MyCamera::MyCamera() : Entity("MyCamera") {
	}
    MyCamera::~MyCamera() {
	}
    void MyCamera::init() {
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
    }
    void MyCamera::draw() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,_winWidth,0,_winHeight,0,-100);
    }
	void MyCamera::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
}
