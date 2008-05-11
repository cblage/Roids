#pragma once
#ifndef MY_BAT_H
#define MY_BAT_H

#include <string>
#include "cg/cg.h"

namespace asteroids {

	class MyBat : public cg::Entity,
		public cg::IDrawListener,
		public cg::IMouseEventListener,
		public cg::IReshapeEventListener
	{
	private:
		double _winHeight;
		cg::Vector2d _position;
		cg::Vector2d _size;

	public:
		MyBat(std::string id);
		~MyBat();
		void init();
		void draw();
        void onMouse(int button, int state, int x, int y);
        void onMouseMotion(int x, int y);
        void onMousePassiveMotion(int x, int y);
		bool isCollision(cg::Vector2d box_position, cg::Vector2d box_size);
        void onReshape(int width, int height);
	};
}

#endif