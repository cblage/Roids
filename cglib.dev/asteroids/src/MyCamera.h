#ifndef MY_CAMERA_H
#define MY_CAMERA_H

#include <string>
#include <cmath>
#include "cg/cg.h"

namespace asteroids {

    class MyCamera : public cg::Entity, 
		public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener
	{
    private:
		double _winWidth, _winHeight;
		float _ang1, _ang2;
		bool _rotateU,_rotateD, _rotateL, _rotateR;

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
	};
}

#endif
