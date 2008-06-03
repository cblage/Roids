#pragma once
#ifndef MY_CAMERA_H
#define MY_CAMERA_H
#pragma message("MyCamera is included")
#include <string>
#include <cmath>
#include "cg/cg.h"
#include "MyCameraController.h"

namespace asteroids {
	class MyCameraController;

    class MyCamera : public cg::Entity, 
		public cg::IDrawListener,
		public cg::IKeyboardEventListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener
	{
    private:
		MyCameraController * _controller;
		double _winWidth, _winHeight;
		float _ang1, _ang2;
		GLfloat _rotLx, _rotLy, _rotLz;
		bool _rotateU,_rotateD, _rotateL, _rotateR;
		bool _debugCamera;

    public:
		void update(unsigned long elapsed_millis);
        MyCamera();
        virtual ~MyCamera();
        void init();
        void draw();
        void onReshape(int width, int height);
		void startRotate(int dir);
		void stopRotate(int dir);
		void rotate(double secs);
		void onKeyPressed(unsigned char key);
		void onKeyReleased(unsigned char key);
		void onSpecialKeyPressed(int key);
        void onSpecialKeyReleased(int key);
	};
}

#endif
