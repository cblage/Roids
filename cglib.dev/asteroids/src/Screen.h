#pragma once
#ifndef SCREEN_H
#define SCREEN_H
#pragma message("Screen is included")

#include <string>
#include "cg/cg.h"

namespace asteroids {
	
	class Screen : public cg::Entity,
		public cg::IDrawOverlayListener,
		public cg::IDrawListener,
		public cg::IReshapeEventListener
	{
	private:
		std::string _message;
		double _winWidth, _winHeight;
	public:
		Screen(std::string id);
		~Screen();
		void init();
		void onReshape(int width, int height);
		std::string getMessage();
		void setMessage(std::string message);
		virtual void drawOverlay();
		virtual void draw();
	};
}

#endif