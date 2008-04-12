#ifndef MY_CAMERA_H
#define MY_CAMERA_H

#include <string>
#include "cg/cg.h"

namespace asteroids {

    class MyCamera : public cg::Entity, 
		public cg::IDrawListener,
		public cg::IReshapeEventListener
	{
    private:
		double _winWidth, _winHeight;

    public:
        MyCamera();
        virtual ~MyCamera();
        void init();
        void draw();
        void onReshape(int width, int height);
	};
}

#endif
