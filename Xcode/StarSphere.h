#pragma once
#ifndef STAR_SPHERE_H
#define STAR_SPHERE_H
#pragma message("StarSphere is included")

#include <string>
#include <vector>
#include <cmath>
#include "cg/cg.h"

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
		double randomBetween(double min, double max);
		void onReshape(int width, int height);
	};
}

#endif
