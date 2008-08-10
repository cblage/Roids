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
#include "LaserShot.h"
#include "GameManager.h"

namespace asteroids {

	LaserShot::LaserShot(std::string id, GameManager * gameManager) : 
		GameEntity(id, gameManager, 'l') {}

	LaserShot::~LaserShot() {
	}
	
	void LaserShot::init() {
		// Read from property file
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		setUniverseDimensions(win.width, win.height); 
		setCollisionCenter(getPosition());
		setStrength(cg::Properties::instance()->getDouble("LASER_STRENGHT"));
		setMass(cg::Properties::instance()->getDouble("LASER_MASS"));
		setHealth(cg::Properties::instance()->getDouble("LASER_HEALTH"));
		_secondsToLive = cg::Properties::instance()->getDouble("LASER_SECONDS_TO_LIVE");
		_radius = cg::Properties::instance()->getDouble("LASER_RADIUS");
		setCollisionRadius(_radius*2);
	}

	void LaserShot::update(unsigned long elapsed_millis) {
		//return; 
		if(isDestroyed() == true)
			return;		

		_secondsToLive -= elapsed_millis / 1000.0;
		if(_secondsToLive <= 0) {
			setDestroyed(true);
			getGameManager()->destroyParticle(_id);
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
			GLboolean blendEnabled, depthTestEnabled;
			blendEnabled = glIsEnabled(GL_BLEND);
			depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
			if(blendEnabled != GL_TRUE) glEnable(GL_BLEND);
			if(depthTestEnabled == GL_TRUE) glDisable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);

			glTranslated(position[0], position[1], 0);
			glColor4d(1, 0, 0, 0.3);
			glutSolidSphere(_radius*0.8, 10, 10);
			glRotated(getRotation(true), 0, 0, 1);
		
			if(blendEnabled != GL_TRUE) glDisable(GL_BLEND);
			if(depthTestEnabled == GL_TRUE) glEnable(GL_DEPTH_TEST);
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

	double LaserShot::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}
}
