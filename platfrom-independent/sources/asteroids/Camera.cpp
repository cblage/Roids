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
#include "Camera.h"
#include "CameraController.h"

namespace asteroids
{

	Camera::Camera() : Entity("Camera")
	{
		_controller = new CameraController(this);
	}
	Camera::~Camera()
	{
	}
	void Camera::init()
	{
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_ang1 = 0;
		_ang2 = 0;

		_rotLx = 0.0f; // Translate screen by using the glulookAt function (left or right)
		_rotLy = 0.0f; // Translate screen by using the glulookAt function (up or down)
		_rotLz = 0.0f; // Translate screen by using the glulookAt function (zoom in or out)

		_debugCamera = (cg::Properties::instance()->getInt("DEBUG_CAMERA") == 1) ? true : false;

		_rotateU = false;
		_rotateD = false;
		_rotateL = false;
		_rotateR = false;
	}

	void Camera::update(unsigned long elapsed_millis)
	{
		double elapsed_seconds = elapsed_millis / 1000.0;
		rotate(elapsed_seconds);
	}

	void Camera::rotate(double secs)
	{
		if (_rotateU == true)
		{
			//_ang1 += 20*secs;
			_rotLy += 80.0f * secs;
		}
		if (_rotateD == true)
		{
			//_ang1 -= 20*secs;
			_rotLy -= 80.0f * secs;
		}
		if (_rotateR == true)
		{
			//_ang2 -= 20*secs;
			_rotLx += 80.0f * secs;
		}
		if (_rotateL == true)
		{
			//_ang2 += 20*secs;
			_rotLx -= 80.0f * secs;
		}
	}

	void Camera::draw()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glRotatef(_ang1,1.0,0,0);
		//glRotatef(_ang2,0,1.0,0);
		glOrtho(0, _winWidth, 0, _winHeight, 0, sqrt(pow(_winWidth, 2) + pow(_winHeight, 2)) * 2);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//gluLookAt( 0, 100, 1000, 0,0,0, 0,1,0);
		//gluLookAt(sqrt(pow(_winWidth, 2) + pow(_winHeight, 2)), sqrt(pow(_winWidth, 2) + pow(_winHeight, 2)), sqrt(pow(_winWidth, 2) + pow(_winHeight, 2)), 0, 0, 0, 0, 0, 1);
		//gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);
		gluLookAt(_rotLx, _rotLy, 200.0 + _rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	void Camera::startRotate(int dir)
	{
		if (!_debugCamera)
			return;

		if (dir == 0)
		{
			_rotateL = true;
		}
		if (dir == 1)
		{
			_rotateR = true;
		}
		if (dir == 2)
		{
			_rotateU = true;
		}
		if (dir == 3)
		{
			_rotateD = true;
		}
		if (dir == 4)
		{
			_rotLx = 0;
			_rotLy = 0;
		}
	}

	void Camera::stopRotate(int dir)
	{
		if (!_debugCamera)
			return;

		if (dir == 0)
		{
			_rotateL = false;
		}
		if (dir == 1)
		{
			_rotateR = false;
		}
		if (dir == 2)
		{
			_rotateU = false;
		}
		if (dir == 3)
		{
			_rotateD = false;
		}
	}

	void Camera::onKeyPressed(unsigned char key)
	{
		_controller->onKeyPressed(key);
	}

	void Camera::onKeyReleased(unsigned char key)
	{
		_controller->onKeyReleased(key);
	}

	void Camera::onSpecialKeyPressed(int key)
	{
		_controller->onSpecialKeyPressed(key);
	}

	void Camera::onSpecialKeyReleased(int key)
	{
		_controller->onSpecialKeyReleased(key);
	}
	void Camera::onReshape(int width, int height)
	{
		_winWidth = width;
		_winHeight = height;
	}
} // namespace asteroids
