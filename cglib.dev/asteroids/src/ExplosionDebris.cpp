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
#include "ExplosionDebris.h"

namespace asteroids {

	ExplosionDebris::ExplosionDebris(std::string id, ParticleManager * particleManager, cg::Vector3d color) : 
		Particle(id, particleManager, 'd'), _color(color) { setHealth(1); setMass(1); }

	ExplosionDebris::~ExplosionDebris() {
	}
	
	void ExplosionDebris::init() {
		// Read from property file
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		setUniverseDimensions(win.width, win.height); 
		setCollisionCenter(getPosition());

		_maxSecondsToLive = cg::Properties::instance()->getDouble("DEBRIS_SECONDS_TO_LIVE");
		_secondsToLive = _maxSecondsToLive;
		_radius = cg::Properties::instance()->getDouble("DEBRIS_RADIUS");
		setCollisionRadius(_radius*2);
	}

	void ExplosionDebris::update(unsigned long elapsed_millis) {
		//return; 
		if(isDestroyed() == true)
			return;		

		_secondsToLive -= elapsed_millis / 1000.0;
		if(_secondsToLive <= 0) {
			setDestroyed(true);
			getParticleManager()->destroyParticle(_id);
			return;
		}

		_alpha = _secondsToLive / _maxSecondsToLive;

		PhysicsObject::update(elapsed_millis);
	}

	void ExplosionDebris::draw() {
		if(isDestroyed() == true)
			return;
		

		cg::Vector2d position = getPosition();
		glPushMatrix(); 
		{
			GLboolean blendEnabled, depthTestEnabled, lightingEnabled;
			blendEnabled = glIsEnabled(GL_BLEND);
			depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
			lightingEnabled = glIsEnabled(GL_LIGHTING);
			if(blendEnabled != GL_TRUE) glEnable(GL_BLEND);
			if(depthTestEnabled == GL_TRUE) glDisable(GL_DEPTH_TEST);
			if(lightingEnabled == GL_TRUE) glDisable(GL_LIGHTING);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);

			glTranslated(position[0], position[1], 0);
			glColor4d(_color[0], _color[1], _color[2], _alpha);
			/*glBegin(GL_POINTS);
			glVertex3d(0, 0, 0);
			glEnd();*/
			glutSolidSphere(_radius*0.5, 3, 3);
			//glRotated(getRotation(true), 0, 0, 1);

			if(lightingEnabled == GL_TRUE) glEnable(GL_LIGHTING);		
			if(depthTestEnabled == GL_TRUE) glEnable(GL_DEPTH_TEST);
			if(blendEnabled != GL_TRUE) glDisable(GL_BLEND);

		}
		glPopMatrix();

		//glFlush();

		/*cg::Vector2d position = getPosition();
		glPushMatrix();
		{
			glTranslated(position[0], position[1], 0);
			glRotated(getRotation(true), 0, 0, 1);
			glColor3d(0, 1, 0);
			glutSolidSphere(_radius, 6, 6);
		}
		glPopMatrix();
		glFlush();*/
		
	}

	void ExplosionDebris::onReshape(int width, int height) {
		if(width > 100 && height > 100) {
			setUniverseDimensions(width,height);
		}
	}

	bool ExplosionDebris::collidesWith(PhysicsObject *pobject) {
		return false;
	}

	double ExplosionDebris::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}
}
