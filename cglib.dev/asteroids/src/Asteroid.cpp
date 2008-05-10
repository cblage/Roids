#include "Asteroid.h"

namespace asteroids {

	Asteroid::Asteroid(std::string id, double scaleFactor, SpaceShip * ship) : 
		cg::Entity(id), 
		_scaleFactor(scaleFactor), 
		_asteroidManager(NULL), 
		_ship(ship) { }
	
	Asteroid::Asteroid(std::string id, SpaceShip * ship) : 
		cg::Entity(id), 
		_scaleFactor(randomBetween(1, 3)), 
		_asteroidManager(NULL), 
		_ship(ship) { }

	Asteroid::Asteroid(std::string id, double scaleFactor, AsteroidManager *  asteroidManager, SpaceShip * ship) : 
		cg::Entity(id), 
		_scaleFactor(scaleFactor), 
		_asteroidManager(asteroidManager), 
		_ship(ship) { }

	Asteroid::Asteroid(std::string id, AsteroidManager * asteroidManager, SpaceShip * ship) : 
		cg::Entity(id), 
		_scaleFactor(randomBetween(1, 3)), 
		_asteroidManager(asteroidManager), 
		_ship(ship) { }



	Asteroid::~Asteroid() {
	}
	
	void Asteroid::init() {
		// Read from property file
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		setUniverseDimensions(win.width, win.height); 
		setVelocity(cg::Vector2d(randomBetween(-100, 100), randomBetween(-100, 100)));
		setPosition(cg::Vector2d((win.width*randomBetween(0.2,1))/2,(win.width*randomBetween(0.2,1)/2)));
		setCollisionCenter(getPosition());
		_destroyed = false;

		cg::Vector3d t;
		int i;
		double x, y, angle, baseAsteroidSize;
		
		baseAsteroidSize = cg::Properties::instance()->getDouble("BASE_ASTEROID_SIZE");
		_radius = baseAsteroidSize * _scaleFactor;
		setCollisionRadius(_radius);

		for (i = 0; i < 12; i++) {
			angle = 2*(3.14)*i/12;
			x = cos(angle)*randomBetween(0.5,0.9)*baseAsteroidSize*_scaleFactor;
			y = sin(angle)*randomBetween(0.5,0.9)*baseAsteroidSize*_scaleFactor;
			t = cg::Vector3d( x, y , 0);
			_asteroid_vector.push_back(t);
			x = cos(angle)*randomBetween(0.5,0.9)*(baseAsteroidSize/2)*_scaleFactor;
			y = sin(angle)*randomBetween(0.5,0.9)*(baseAsteroidSize/2)*_scaleFactor;
			t = cg::Vector3d( x, y, 10);
			_asteroid_vector2.push_back(t);


		} 
	}

	void Asteroid::update(unsigned long elapsed_millis) {
		if(_destroyed == true)
			return;		
		
		PhysicsObject::update(elapsed_millis);

		if(collidesWith(_ship)) {
			_destroyed = true;
				if(_asteroidManager != NULL) {
					int newAsteroids = abs(int(_scaleFactor/2 + 0.5));
					double newScaleFactor = 0;
					
					if(newAsteroids > 1) {
						newScaleFactor = _scaleFactor * (1/(double)newAsteroids);
					} else if(newAsteroids == 1) {
						newScaleFactor = 0.5 * _scaleFactor;
						newAsteroids = 2;
					}
					_asteroidManager->createAsteroids(newAsteroids, newScaleFactor, getPosition());
					_asteroidManager->destroyAsteroid(_id);
				}
		}	

	}

	void Asteroid::draw() {
		cg::Vector3d t;
		cg::Vector2d position = getPosition();

		glPushMatrix();
		{
			glTranslated(position[0], position[1], 0);
			glRotated(getRotation(true), 0, 0, 1);
			glRotated(180,0,1,0);
			
			std::vector<cg::Vector3d>::iterator q = _asteroid_vector2.begin( );
			std::vector<cg::Vector3d>::iterator pBegin = _asteroid_vector.begin( );
			std::vector<cg::Vector3d>::iterator qBegin = _asteroid_vector2.begin( );
			
			glBegin(GL_QUAD_STRIP);{
				
glColor3d(0.9,0.9,0.9);
			for (std::vector<cg::Vector3d>::iterator p = _asteroid_vector.begin( );p != _asteroid_vector.end();p++) {
				 
				   glVertex3f((*p)[0],(*p)[1],(*p)[2]);
					glColor3d(0.4,0.4,0.4);
				   glVertex3f((*q)[0],(*q)[1],(*q)[2]);
				   glColor3d(0.9,0.9,0.9);
				   q++;
			}
			glVertex3f((*pBegin)[0],(*pBegin)[1],(*pBegin)[2]);
			glColor3d(0.4,0.4,0.4);
			glVertex3f((*qBegin)[0],(*qBegin)[1],(*qBegin)[2]);
			
			
			glEnd();
			}
			
			glBegin(GL_TRIANGLE_STRIP);{
		
			
			
			

			for (std::vector<cg::Vector3d>::iterator q = _asteroid_vector2.begin( );q != _asteroid_vector2.end();q++) {
				 glColor3d(0.4,0.4,0.4);
				   glVertex3f((*q)[0],(*q)[1],(*q)[2]);
glColor3d(0.8,0.8,0.8);
				   glVertex3f(1,1,20);
			}
			
			glVertex3f((*qBegin)[0],(*qBegin)[1],(*qBegin)[2]);
		
			
			glEnd();

			}

		glFlush();
		glPopMatrix();
		}
	}

	void Asteroid::onReshape(int width, int height) {
		if(width > 100 && height > 100) {
			setUniverseDimensions(width,height);
		}
	}

	double Asteroid::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}
	void Asteroid::onMouse(int button, int state, int x, int y) {
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && _destroyed == false){
			cg::Vector2d universeDimensions = getUniverseDimensions();
			if(length(cg::Vector2d(x, universeDimensions[1] - y) - getPosition()) < _radius) {
				_destroyed = true;
				if(_asteroidManager != NULL) {
					int newAsteroids = abs(int(_scaleFactor/2 + 0.5));
					double newScaleFactor = 0;
					
					if(newAsteroids > 1) {
						newScaleFactor = _scaleFactor * (1/(double)newAsteroids);
					} else if(newAsteroids == 1) {
						newScaleFactor = 0.5 * _scaleFactor;
						newAsteroids = 2;
					}
					_asteroidManager->createAsteroids(newAsteroids, newScaleFactor, getPosition());
					_asteroidManager->destroyAsteroid(_id);
				}
			}	
		}
	}
	void Asteroid::onMouseMotion(int x, int y) {
	}
	void Asteroid::onMousePassiveMotion(int x, int y) {
	}
}
