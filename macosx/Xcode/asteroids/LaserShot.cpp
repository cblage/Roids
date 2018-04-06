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
		_secondsToLiveMax = cg::Properties::instance()->getDouble("LASER_SECONDS_TO_LIVE");
		_secondsToLive = _secondsToLiveMax;
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
		
		
		if(_secondsToLive > 0) {
			glPushMatrix();
			{
				glPushAttrib(GL_COLOR_BUFFER_BIT);			
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA,GL_ONE);				
				glTranslated(position[0], position[1], 0);
				glColor4d(1, 0.2, 0.2, _secondsToLive/_secondsToLiveMax*0.8);
				GLfloat laserEmission[] = { 0.5*_secondsToLive/_secondsToLiveMax, 0.1*_secondsToLive/_secondsToLiveMax, 0.1*_secondsToLive/_secondsToLiveMax, 0.0f};
				glMaterialfv(GL_FRONT, GL_EMISSION, laserEmission);		
				glMateriali(GL_FRONT, GL_SHININESS, 128*_secondsToLive/_secondsToLiveMax);								
				
				glutSolidSphere(_radius*0.8, 10, 10);
				glPopAttrib();
				
			}
			glPopMatrix();		
		}
		
		

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

	bool LaserShot::collidesWith(PhysicsObject *pobject) {
		if(isDestroyed() == true)
			return false;
		//else
		return PhysicsObject::collidesWith(pobject);
	}
}


