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
#ifndef STAR_SPHERE_H
#define STAR_SPHERE_H
#pragma message("StarSphere is included")

#include <string>
#include <vector>
#include <cmath>
#include <cg/cg.h>

namespace asteroids {
	const double PI3  = 4.0*atan(1.0);
    
	class StarSphere : public cg::Entity, 
		public cg::IDrawListener,
		public cg::IReshapeEventListener
	{
    private:
		std::vector<cg::Vector3d> _stars;
		double _winWidth, _winHeight, _starDensity, _starSphereRadius;
    public:
        StarSphere();
        virtual ~StarSphere();
        void init();
        void draw();
		cg::Vector3d getRandomStar();
		void onReshape(int width, int height);
	};
}

#endif


