#include "StarSphere.h"

namespace asteroids {

    StarSphere::StarSphere() : Entity("StarSphere") {
	}
    StarSphere::~StarSphere() {
	}
    void StarSphere::init() {
		//_numberOfStars = cg::Properties::instance()->getInt("STAR_NUM");
		//_starSphereRadius = cg::Properties::instance()->getInt("STAR_SPHERE_RADIUS");
		_starDensity = cg::Properties::instance()->getDouble("STAR_DENSITY");
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;

		for(int i = 0; i < _starDensity*_winWidth*_winHeight; i++) {
			_stars.push_back(getRandomStar());
		}
    }
	cg::Vector3d StarSphere::getRandomStar() {
		//double theta, omega;
		//theta = randomBetween(0, 6.29);
		//omega = randomBetween(0, 6.29);
		//return cg::Vector3d(_starSphereRadius * cos(theta) * sin(omega), _starSphereRadius * sin(theta) * sin(omega), _starSphereRadius * cos(omega));
		return cg::Vector3d(randomBetween(0, _winWidth), randomBetween(0, _winHeight), 10);
	}
	
	void StarSphere::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
		_stars.clear();
		for(int i = 0; i < _starDensity*_winWidth*_winHeight; i++) {
			_stars.push_back(getRandomStar());
		}
	}

	void StarSphere::draw() {
		for (std::vector<cg::Vector3d>::iterator p = _stars.begin();  p != _stars.end(); ++p) {
			glPushMatrix();
			{
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				//glTranslated(_winWidth/2, _winHeight/2, 0);
				glTranslated((*p)[0], (*p)[1], (*p)[2]);
				glColor3d(1, 1, 1);
				glutSolidSphere(1, 3, 3);
			}
			glPopMatrix();
			glFlush();
		}
    }
	double StarSphere::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}
}
