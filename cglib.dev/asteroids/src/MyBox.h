#ifndef MY_BOX_H
#define MY_BOX_H

#include <string>
#include "cg/cg.h"
#include "MyBat.h"

namespace asteroids {

	class MyBox : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener
	{
	private:
		cg::Vector2d _position, _size;
		cg::Vector2d _velocity;
		cg::Vector3d _color;
		double _winWidth, _winHeight;
		MyBat* _bat;

		double randomBetween(double min, double max);

	public:
		MyBox(std::string id);
		~MyBox();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
        void onReshape(int width, int height);
	};
}

#endif