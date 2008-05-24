#pragma once
#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H
#pragma message("ApplicationController is included")

#include "cg/cg.h"
#include "MyApp.h"

namespace asteroids {
	class MyApp;

	class ApplicationController : public cg::Entity,
		public cg::IKeyboardEventListener
	{
	public:
		ApplicationController(MyApp* application);
		~ApplicationController();
		void init();
		void onKeyPressed(unsigned char key);
		void onKeyReleased(unsigned char key);
		void onSpecialKeyPressed(int key);
		void onSpecialKeyReleased(int key);

	private:
		MyApp * _application;
	};


}

#endif