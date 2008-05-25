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
		int colorPick=0;
		for (std::vector<cg::Vector3d>::iterator p = _stars.begin();  p != _stars.end(); ++p) {
			glPushMatrix();
			{
				glTranslated(_winWidth/2, _winHeight/2, 0);
				glTranslated((*p)[0], (*p)[1], (*p)[2]);
				colorPick=rand()%2;
					switch(colorPick){
						case 0 :
							glColor3d(1,1,1);
							break;
						case 1 :
							glColor3d(0.8,0.8,0.8);
							break;
						default:
							glColor3d(1,1,1);
				}
				glutSolidSphere(1, 6, 6);
			}
			glPopMatrix();
			glFlush();
		}
    }
	double StarSphere::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}
}
