#include "LaserShot.h"

namespace asteroids {

	LaserShot::LaserShot(std::string id, ParticleManager * particleManager) : 
		Particle(id, 250, particleManager) { setHealth(1); setMass(1000); }

	LaserShot::~LaserShot() {
	}
	
	void LaserShot::init() {
		// Read from property file
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		setUniverseDimensions(win.width, win.height); 
		setCollisionCenter(getPosition());

		_secondsToLive = cg::Properties::instance()->getDouble("LASER_SECONDS_TO_LIVE");
		_radius = cg::Properties::instance()->getDouble("LASER_RADIUS");
		setCollisionRadius(_radius*2);
	}

	void LaserShot::update(unsigned long elapsed_millis) {
		if(isDestroyed() == true)
			return;		

		_secondsToLive -= elapsed_millis / 1000.0;
		if(_secondsToLive <= 0) {
			setDestroyed(true);
			getParticleManager()->destroyParticle(_id);
			return;
		}

		PhysicsObject::update(elapsed_millis);
	}

	void LaserShot::draw() {
		if(isDestroyed() == true)
			return;		

		cg::Vector2d position = getPosition();
		glPushMatrix();
		{
			glTranslated(position[0], position[1], 0);
			glRotated(getRotation(true), 0, 0, 1);
			glColor3d(1, 0, 0);
			glutSolidSphere(_radius, 6, 6);
		}
		glPopMatrix();
		glFlush();
		
	}

	void LaserShot::onReshape(int width, int height) {
		if(width > 100 && height > 100) {
			setUniverseDimensions(width,height);
		}
	}

	bool LaserShot::collidesWith(PhysicsObject *pobject) {
		if(isDestroyed() == true)
			return false;
		//else
		return PhysicsObject::collidesWith(pobject);
	}
}
