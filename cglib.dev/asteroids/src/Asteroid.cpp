#include "Asteroid.h"

namespace asteroids {

	Asteroid::Asteroid(std::string id, double scaleFactor, SpaceShip * ship) : cg::Entity(id), _scaleFactor(scaleFactor), _asteroidManager(NULL), _ship(ship) {
		//_accelerator = new AsteroidAccelerator(this);
		//_rotator = new AsteroidRotator(this);
		_physics = new PhysicsEngine();
	}
	
	Asteroid::Asteroid(std::string id, SpaceShip * ship) : cg::Entity(id), _scaleFactor(randomBetween(1, 3)), _asteroidManager(NULL), _ship(ship) {
		//_accelerator = new AsteroidAccelerator(this);
		//_rotator = new AsteroidRotator(this);
		_physics = new PhysicsEngine();
	}

	Asteroid::Asteroid(std::string id, double scaleFactor, AsteroidManager *  asteroidManager, SpaceShip * ship) : cg::Entity(id), _scaleFactor(scaleFactor), _asteroidManager(asteroidManager), _ship(ship) {
		//_accelerator = new AsteroidAccelerator(this);
		//_rotator = new AsteroidRotator(this);
		_physics = new PhysicsEngine();
	}

	Asteroid::Asteroid(std::string id, AsteroidManager * asteroidManager, SpaceShip * ship) : cg::Entity(id), _scaleFactor(randomBetween(1, 3)), _asteroidManager(asteroidManager), _ship(ship) {
		//_accelerator = new AsteroidAccelerator(this);
		//_rotator = new AsteroidRotator(this);
		_physics = new PhysicsEngine();
	}



	Asteroid::~Asteroid() {
		//delete(_accelerator);
		//delete(_rotator);
		delete(_physics);
	}
	
	void Asteroid::init() {
		// Read from property file
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_physics->setUniverseDimensions(win.width, win.height); 
		
		_physics->setVelocity(cg::Vector2d(randomBetween(-100, 100), randomBetween(-100, 100)));
		
		_physics->setPosition(cg::Vector2d((_winWidth*randomBetween(0.2,1))/2,(_winHeight*randomBetween(0.2,1)/2)));
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
		} 
	}

	void Asteroid::update(unsigned long elapsed_millis) {
		if(_destroyed == true)
			return;
		
		
		_physics->update(elapsed_millis);

		setCollisionCenter(getPosition());

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
		if(_destroyed == true)
			return;
		cg::Vector2d position = getPosition();

		glPushMatrix();
		{
			glTranslated(position[0], position[1], 0);
			glRotated(getRotation(true), 0, 0, 1);
			glColor3d(0.5,0.9,0.5);
			glLineWidth(1.5);
			glBegin(GL_LINE_LOOP);
			{
				for (std::vector<cg::Vector3d>::iterator p = _asteroid_vector.begin( );p != _asteroid_vector.end( ); ++p) {
					glVertex3f((*p)[0],(*p)[1],(*p)[2]);
				}
			}
			glEnd();
		}
		glFlush();
		glPopMatrix();
	}

	void Asteroid::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
		_physics->setUniverseDimensions(_winWidth, _winHeight); 
		
	}

	void Asteroid::accelerate(double factor, bool withRotation) {	
		_physics->accelerate(factor, withRotation);
	}

	void Asteroid::accelerate(double factor, bool withRotation, cg::Vector2d minVelocity) {	
		_physics->accelerate(factor, withRotation, minVelocity);
	}
	
	void Asteroid::startAcceleration(double factor, bool withRotation) {
		_physics->startAcceleration(factor, withRotation);
	}
	void Asteroid::startAcceleration(double factor, bool withRotation, cg::Vector2d minVelocity) {
		_physics->startAcceleration(factor, withRotation, minVelocity);
	}

	void Asteroid::stopAcceleration() {
		_physics->stopAcceleration();
	}

	void Asteroid::startRotation(double factor) {
		_physics->startRotator(factor);
	}

	void Asteroid::stopRotation() {
		_physics->stopRotator();
	}
	
	
	void Asteroid::setVelocity(cg::Vector2d velocity) {
		_physics->setVelocity(velocity);
	}

	cg::Vector2d Asteroid::getVelocity() const {
		return _physics->getVelocity();
	}

	cg::Vector2d Asteroid::getPosition() const {
		return _physics->getPosition();
	}

	cg::Vector2d Asteroid::getNormalizedVelocity() const {
		return _physics->getNormalizedVelocity();
	}

	double Asteroid::getRotation() const {
		return _physics->getRotation();
	}
	double Asteroid::getRotation(bool inDegrees) const{
		return _physics->getRotation(inDegrees);
	}
	cg::Vector2d Asteroid::getUniverseDimensions(void) {
		return cg::Vector2d(_winWidth, _winHeight);
	}
	void Asteroid::setPosition(cg::Vector2d position) {
		_physics->setPosition(position);
	}
	
	double Asteroid::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}
	void Asteroid::onMouse(int button, int state, int x, int y) {
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && _destroyed == false){
			if(length(cg::Vector2d(x, _winHeight - y) - getPosition()) < _radius) {
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