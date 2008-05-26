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
		double red, green, blue, radius;
		for (std::vector<cg::Vector3d>::iterator p = _stars.begin();  p != _stars.end(); ++p) {
			glPushMatrix();
			{
				glTranslated(_winWidth/2, _winHeight/2, 0);
				colorPick=rand()%10000;
				switch(colorPick){
					case 1 :
						red = 1;
						green = 0;
						blue = 0;
						radius = 3;
						break;
					case 2 :
						red = 0;
						green = 1;
						blue = 0;
						radius = 3;
						break;
					case 3 :
						red = 0;
						green = 0;
						blue = 1;
						radius = 2;
						break;
					case 4 :
						red = 0.5;
						green = 0.5;
						blue = 0.5;
						radius = 2;
						break;
					case 5 :
						red = 0.5;
						green = 0.5;
						blue = 0.5;
						radius = 2;
						break;
					case 6 :
						red = 0.5;
						green = 0.5;
						blue = 0.5;
						radius = 3;
						break;
					case 7 :
						red = 0.5;
						green = 0.5;
						blue = 0.5;
						radius = 3;
						break;
					case 8 :
						red = 0.5;
						green = 0.5;
						blue = 0.5;
						radius = 3;
						break;
					case 9 :
						red = 0.5;
						green = 0.5;
						blue = 0.5;
						radius = 3;
						break;
					case 10 :
						red = 0.5;
						green = 0.5;
						blue = 0.5;
						radius = 2;
						break;

					default:
						red = 1;
						green = 1;
						blue = 1;
						radius = 1;
				}


				glPushMatrix(); 
				{
					glTranslated((*p)[0], (*p)[1], (*p)[2]);
					glColor3d(red, green, blue);
					glutSolidSphere(radius, 3, 3);
				}
				glPopMatrix();
			
				glPushMatrix(); 
				{
					GLboolean blendEnabled, depthTestEnabled;
					blendEnabled = glIsEnabled(GL_BLEND);
					depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
					if(blendEnabled != GL_TRUE) glEnable(GL_BLEND);
					if(depthTestEnabled == GL_TRUE) glDisable(GL_DEPTH_TEST);
					glBlendFunc(GL_SRC_ALPHA,GL_ONE);
					
					for(int i = 0; i < 4; i++) {
						glPushMatrix(); 
						{
							double x, y, angle;
							angle = 2 * 3.14 * i / 4;
							x = cos(angle);
							y = sin(angle);
							glTranslated((*p)[0]+x, (*p)[1]+y, (*p)[2]);
							glColor4d(red, green, blue, 0.1);
							glutSolidSphere(radius, 6, 6);
						}
						glPopMatrix();
					}


					if(blendEnabled != GL_TRUE) glDisable(GL_BLEND);
					if(depthTestEnabled == GL_TRUE) glEnable(GL_DEPTH_TEST);
				}
				glPopMatrix();

			}
			glPopMatrix();
			glFlush();
		}
    }
	double StarSphere::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}
}
