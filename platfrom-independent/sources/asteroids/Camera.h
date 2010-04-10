/*
 Roids!
 Copyright (C) 2008 Carlos Lage, Tiago Coelho, Eduardo Castanho

 This file is part of Roids!.

 Roids! is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 Roids! is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Roids!; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#pragma message("Camera is included")
#include <string>
#include <cmath>
#include <cg/cg.h>


namespace asteroids {
	class CameraController;

    class Camera : public cg::Entity, 
		public cg::IDrawListener,
		public cg::IKeyboardEventListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener
	{
    private:
		CameraController * _controller;
		double _winWidth, _winHeight;
		float _ang1, _ang2;
		GLfloat _rotLx, _rotLy, _rotLz;
		bool _rotateU,_rotateD, _rotateL, _rotateR;
		bool _debugCamera;

    public:
		void update(unsigned long elapsed_millis);
        Camera();
        virtual ~Camera();
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


