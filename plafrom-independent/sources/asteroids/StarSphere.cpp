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
#include "StarSphere.h"

namespace asteroids {

    StarSphere::StarSphere() : Entity("StarSphere") {
	}
    StarSphere::~StarSphere() {
	}
    void StarSphere::init() {
		_starDensity = cg::Properties::instance()->getDouble("STAR_DENSITY");
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		
		_starSphereRadius = sqrt(pow(_winWidth, 2) + pow(_winHeight, 2))*1.5;

		double numStars = _starDensity * pow(_starSphereRadius, 2) * 4 * PI3;
		
		for(int i = 0; i < numStars; i++) {
			_stars.push_back(getRandomStar());
		}
    }
	cg::Vector3d StarSphere::getRandomStar() {
		double theta, omega;
		theta = randomBetween(0, 6.29);
		omega = randomBetween(0, 6.29);
		return cg::Vector3d(_starSphereRadius * cos(theta) * sin(omega), _starSphereRadius * sin(theta) * sin(omega), _starSphereRadius * cos(omega));
	}
	
	void StarSphere::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
		_starSphereRadius = sqrt(pow(_winWidth, 2) + pow(_winHeight, 2))*1.5;
		double numStars = _starDensity * pow(_starSphereRadius, 2) * 4 * PI3;
		_stars.clear();
		for(int i = 0; i < numStars; i++) {
			_stars.push_back(getRandomStar());
		}
	}

	void StarSphere::draw() {
		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		glEnableClientState(GL_VERTEX_ARRAY);
		glPointSize(1.1);
		glPushMatrix(); 
		{
			glTranslated(_winWidth/2, _winHeight/2, 0);
			glVertexPointer(3, GL_DOUBLE, 0, &_stars[0]);
			glColor3d(1, 1, 1);
			glDrawArrays(GL_POINTS, 0, (GLsizei) _stars.size());
			
			glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			glPushMatrix(); 
			{
				glEnable(GL_BLEND); 
				glDisable(GL_DEPTH_TEST); 
				glBlendFunc(GL_SRC_ALPHA,GL_ONE); 
				
				glColor4d(1, 1, 1, 0.1);
				for(int i = 0; i < 4; i++) { 
					glPushMatrix();  
					{ 
						double x, y, angle; 
						angle = 2 * 3.14 * i / 4; 
						x = cos(angle); 
						y = sin(angle); 
						glTranslated(x, y, 0); 
						glDrawArrays(GL_POINTS, 0, (GLsizei) _stars.size());
					} 
					glPopMatrix(); 
				}
			}
			glPopMatrix();
			glPopAttrib();
		}
		glPopMatrix();	
		
		
		glDisableClientState(GL_VERTEX_ARRAY);
		glPopAttrib();
    }
	double StarSphere::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}
}


