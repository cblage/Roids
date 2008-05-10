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
		_ang=0;
    }
    void MyCamera::draw() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
        glOrtho(0,_winWidth,0,_winHeight,0, sqrt(pow(_winWidth, 2) + pow(_winHeight, 2))*2);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//gluLookAt(sqrt(pow(_winWidth, 2) + pow(_winHeight, 2)), sqrt(pow(_winWidth, 2) + pow(_winHeight, 2)), sqrt(pow(_winWidth, 2) + pow(_winHeight, 2)), 0, 0, 0, 0, 0, 1);
		//glRotatef(0.5*_ang++,1,1,1);

	}
	void MyCamera::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
}
