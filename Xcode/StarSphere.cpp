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
		glPushAttrib(GL_LIGHTING_BIT | GL_POINT_SMOOTH);
		glDisable(GL_LIGHTING);
		glEnableClientState(GL_VERTEX_ARRAY);
		glPushMatrix(); 
		{
			//glEnable(GL_POINT_SMOOTH);
			glPointSize(1.1);
			glTranslated(_winWidth/2, _winHeight/2, 0);
			glVertexPointer(3, GL_DOUBLE, 0, &_stars[0]);
			glColor3d(1, 1, 1);
			glDrawArrays(GL_POINTS, 0, _stars.size());
		}
		glPopMatrix();	
		glDisableClientState(GL_VERTEX_ARRAY);
		glPopAttrib();
    }
	double StarSphere::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}
}
