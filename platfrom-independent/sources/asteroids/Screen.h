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
#ifndef SCREEN_H
#define SCREEN_H
#pragma message("Screen is included")

#include <string>
#include <cg/cg.h>

namespace asteroids {
	
	class Screen : public cg::Entity,
		public cg::IDrawOverlayListener,
		public cg::IDrawListener,
		public cg::IReshapeEventListener
	{
	protected:
		std::string _message;
		double _winWidth, _winHeight;
		double _messageX, _messageY;
	public:
		Screen(std::string id);
		~Screen();
		void init();
		void onReshape(int width, int height);
		std::string getMessage();
		void setMessage(std::string message);
		virtual void drawOverlay();
		virtual void draw();
		virtual cg::Vector2d getMessagePosition();
		virtual void setMessagePosition(double x, double y);
	};
}

#endif

