#ifndef STAR_SPHERE_H
#define STAR_SPHERE_H

#include <string>
#include <vector>
#include "cg/cg.h"

namespace asteroids {

    class StarSphere : public cg::Entity, 
		public cg::IDrawListener,
		public cg::IReshapeEventListener
	{
    private:
		//int _numberOfStars, _starSphereRadius;
		std::vector<cg::Vector3d> _stars;
		double _winWidth, _winHeight, _starDensity;
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
