#include "Asteroid.h"

namespace asteroids {

	Asteroid::Asteroid(std::string id, double scaleFactor, ParticleManager *  particleManager) : 
		Particle(id, particleManager, 'a'),
		_scaleFactor(scaleFactor) {
		setMass(_scaleFactor * 10000);
		setHealth(getMass());
	}

	Asteroid::Asteroid(std::string id, ParticleManager * particleManager) : 
		Particle(id, particleManager, 'a'),
		_scaleFactor(randomBetween(1, 3)) { 
		setMass(_scaleFactor * 10000);
		setHealth(getMass());
	}

	Asteroid::~Asteroid() {
	}
	
	void Asteroid::init() {
		// Read from property file
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		setUniverseDimensions(win.width, win.height); 
		setVelocity(cg::Vector2d(randomBetween(-100, 100), randomBetween(-100, 100)));
		setCollisionCenter(getPosition());

		
		_invulSeconds = cg::Properties::instance()->getDouble("ASTEROID_INVUL_SECONDS");

		cg::Vector3d t;
		int i;
		double x, y, angle, baseAsteroidSize;
		
		baseAsteroidSize = cg::Properties::instance()->getDouble("BASE_ASTEROID_SIZE");
		_radius = baseAsteroidSize * _scaleFactor;
		setCollisionRadius(_radius*0.75);
		startRotation(randomBetween(-length(getVelocity()), length(getVelocity())));

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
		if(isDestroyed() == true)
			return;
		
		if((_invulSeconds - elapsed_millis/1000.0)< 0) {
			_invulSeconds = 0;
		} else {
			_invulSeconds -= elapsed_millis/1000.0;
		}

		PhysicsObject::update(elapsed_millis);
		checkCollisions(elapsed_millis);

		setRotationFactor(length(getVelocity())*getRotationFactor()/getRotationFactor());
	}

	void Asteroid::draw() {
		if(isDestroyed() == true)
			return;		

		cg::Vector3d t;
		cg::Vector2d position = getPosition();

		glPushMatrix();
		{
			glTranslated(position[0], position[1], 0);
			glRotated(getRotation(true), 0, 0, 1);
			
			std::vector<cg::Vector3d>::iterator q = _asteroid_vector2.begin( );
			std::vector<cg::Vector3d>::iterator pBegin = _asteroid_vector.begin( );
			std::vector<cg::Vector3d>::iterator qBegin = _asteroid_vector2.begin( );
			
			glBegin(GL_QUAD_STRIP);
			{
				cg::Vector3d normal = cg::Vector3d(0, 0, 0);
				glColor3d(0.9,0.9,0.9);
				for (std::vector<cg::Vector3d>::iterator p = _asteroid_vector.begin( );p != _asteroid_vector.end();p++) {		 
					normal = normalize(cg::Vector3d((*p)[0],(*p)[1],(*p)[2]));
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f((*p)[0],(*p)[1],(*p)[2]);
					glColor3d(0.4,0.4,0.4);
					normal = normalize(cg::Vector3d((*q)[0],(*q)[1],(*q)[2]));
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f((*q)[0],(*q)[1],(*q)[2]);
					glColor3d(0.9,0.9,0.9);
					q++;
				}
				glVertex3f((*pBegin)[0],(*pBegin)[1],(*pBegin)[2]);
				glColor3d(0.4,0.4,0.4);
				glVertex3f((*qBegin)[0],(*qBegin)[1],(*qBegin)[2]);
			}
			glEnd();
			
			glBegin(GL_TRIANGLE_STRIP);
			{
				cg::Vector3d normal = cg::Vector3d(0, 0, 0);
				for (std::vector<cg::Vector3d>::iterator q = _asteroid_vector2.begin( );q != _asteroid_vector2.end();q++) {
					glColor3d(0.4,0.4,0.4);
					normal = normalize(cg::Vector3d((*q)[0],(*q)[1],(*q)[2]));
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f((*q)[0],(*q)[1],(*q)[2]);
					glColor3d(0.8,0.8,0.8);
					glVertex3f(1,1,_radius);
					glNormal3f(1, 1, _radius);
				}				
				glVertex3f((*qBegin)[0],(*qBegin)[1],(*qBegin)[2]);
			}
			glEnd();
					glBegin(GL_QUAD_STRIP);
			{
				q = _asteroid_vector2.begin( );
				cg::Vector3d normal = cg::Vector3d(0, 0, 0);
				glColor3d(0.9,0.9,0.9);
				for (std::vector<cg::Vector3d>::iterator p = _asteroid_vector.begin( );p != _asteroid_vector.end();p++) {		 
					normal = normalize(cg::Vector3d((*p)[0],(*p)[1],-(*p)[2]));
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f((*p)[0],(*p)[1],-((*p)[2]));
					glColor3d(0.4,0.4,0.4);
					normal = normalize(cg::Vector3d((*q)[0],(*q)[1],-(*q)[2]));
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f((*q)[0],(*q)[1],-(*q)[2]);
					glColor3d(0.9,0.9,0.9);
					q++;
				}
				glVertex3f((*pBegin)[0],(*pBegin)[1],-(*pBegin)[2]);
				glColor3d(0.4,0.4,0.4);
				glVertex3f((*qBegin)[0],(*qBegin)[1],-(*qBegin)[2]);
			}
			glEnd();
			
			glBegin(GL_TRIANGLE_STRIP);
			{
				cg::Vector3d normal = cg::Vector3d(0, 0, 0);
				for (std::vector<cg::Vector3d>::iterator q = _asteroid_vector2.begin( );q != _asteroid_vector2.end();q++) {
					glColor3d(0.4,0.4,0.4);
					normal = normalize(cg::Vector3d((*q)[0],(*q)[1],-(*q)[2]));
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f((*q)[0],(*q)[1],-(*q)[2]);
					glColor3d(0.8,0.8,0.8);
					glVertex3f(1,1,-_radius);
					glNormal3f(1, 1, -_radius);
				}				
				glVertex3f((*qBegin)[0],-(*qBegin)[1],-(*qBegin)[2]);
			}
			glEnd();
		}
		glPopMatrix();
		glFlush();

		//cg::Vector2d position = getPosition();
		/*glPushMatrix();
		{
			glTranslated(position[0], position[1], 0);
			//glRotated(getRotation(true), 0, 0, 1);
			glColor3d(1, 0, 0);
			glutSolidSphere(getCollisionRadius(), 30, 30);
			//glColor3d(0, 1, 0);
			//glutWireSphere(getCollisionRadius()-5, 30, 30);
			glColor3d(0, 0, 1);
			glutWireSphere(getCollisionRadius()-5, 30, 30);
		}
		glPopMatrix();
		glFlush();*/
	}

	void Asteroid::onReshape(int width, int height) {
		if(width > 100 && height > 100) {
			setUniverseDimensions(width,height);
		}
	}

	double Asteroid::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}

	bool Asteroid::collidesWith(PhysicsObject *pobject) {
		if(isDestroyed() == true || _invulSeconds > 0)
			return false;
		//else
		return PhysicsObject::collidesWith(pobject);
	}

	void Asteroid::checkCollisions(double long elapsed_millis) {
		if(_invulSeconds > 0)
			return;

		Particle::checkCollisions(elapsed_millis);
	}

	void Asteroid::destroy(void) {
		int newAsteroids = abs(int(_scaleFactor/2 + 0.5));
		double newScaleFactor = 0;
		double radius = 0;
		
		if(newAsteroids > 1) {
			newScaleFactor = _scaleFactor * (1/(double)newAsteroids);
		} else if(newAsteroids == 1) {
			newScaleFactor = 0.5 * _scaleFactor;
			newAsteroids = 2;
		}
		radius = getCollisionRadius();
		getParticleManager()->createAsteroids(newAsteroids, newScaleFactor, radius, getPosition());

		Particle::destroy();
	}

		void Asteroid::drawOverlay() {
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		GLboolean lightingEnabled;
		lightingEnabled = glIsEnabled(GL_LIGHTING);
		if(lightingEnabled == GL_TRUE) glDisable(GL_LIGHTING);
		
		cg::Vector2d position = getPosition();
		cg::Vector2d windowSize = cg::Vector2d(win.width, win.height);
		cg::Vector2d relativePosition = position / windowSize;
		std::ostringstream aaa;
		double tamanho;
		tamanho = 5;
		aaa << "a";
		cg::Util::instance()->drawStrokeString(aaa.str(), win.width-win.width/tamanho +  relativePosition[0]*win.width/tamanho , relativePosition[1]*win.height/tamanho,0.15,false,2,0.4,0.7,0.9,1);
		if(lightingEnabled == GL_TRUE) glEnable(GL_LIGHTING);
	}
}
