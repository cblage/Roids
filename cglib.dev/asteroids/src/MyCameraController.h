#pragma once
#ifndef MYCAMERA_CONTROLLER_H
#define MYCAMERA_CONTROLLER_H
#pragma message("MyCameraController is included")

#include "cg/cg.h"
#include "MyCamera.h"

namespace asteroids {
	class MyCamera;

	class MyCameraController : public cg::Entity,
		public cg::IKeyboardEventListener
	{
	public:
		MyCameraController(MyCamera* camera);
		~MyCameraController();
		void init();
        void onKeyPressed(unsigned char key);
        void onKeyReleased(unsigned char key);
        void onSpecialKeyPressed(int key);
        void onSpecialKeyReleased(int key);

	private:
		MyCamera * _camera;
	};


}

#endif