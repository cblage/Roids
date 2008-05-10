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
		_ang1=0;
		_ang2=0;
		_rotateU = false;
		_rotateD = false;
		_rotateL = false;
		_rotateR = false;

    }
	
	void MyCamera::update(unsigned long elapsed_millis) {
		double elapsed_seconds = elapsed_millis / 1000.0;	
		rotate(elapsed_seconds);
	}
	
	void MyCamera::rotate(double secs){
		if (_rotateU == true) {
				_ang1 += 20*secs;
		}
		if (_rotateD == true){
				_ang1 -= 20*secs;
		}
		if (_rotateR == true){
				_ang2 -= 20*secs; 
		}
		if (_rotateL == true){
				_ang2 += 20*secs; 
		}
	}

	void MyCamera::draw() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glRotatef(_ang1,1.0,0,0);
		glRotatef(_ang2,0,1.0,0);
		glOrtho(0,_winWidth,0,_winHeight,0, sqrt(pow(_winWidth, 2) + pow(_winHeight, 2))*2);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//gluLookAt( 0, 100, 1000, 0,0,0, 0,1,0);
		//gluLookAt(sqrt(pow(_winWidth, 2) + pow(_winHeight, 2)), sqrt(pow(_winWidth, 2) + pow(_winHeight, 2)), sqrt(pow(_winWidth, 2) + pow(_winHeight, 2)), 0, 0, 0, 0, 0, 1);
		
	}

	void MyCamera::startRotate(int dir){
		if (dir == 0){
			_rotateL = true;
		}
		if (dir == 1){
			_rotateR = true;
		}
		if (dir == 2){
			_rotateU = true;
		}
		if (dir == 3){
			_rotateD = true;
		}
		if (dir == 4){
			_ang1=0;
			_ang2=0;
		}
	}

	void MyCamera::stopRotate(int dir){
		if (dir == 0){
			_rotateL = false;
		}
		if (dir == 1){
			_rotateR = false;
		}
		if (dir == 2){
			_rotateU = false;
		}
		if (dir == 3){
			_rotateD = false;
		}
	}

	void MyCamera::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
}
