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
#include "GameManager.h"

namespace asteroids {
	GameManager::GameManager(std::string id, MyApp *application) : ParticleManager(id), _application(application) {
		_shipsLeft = cg::Properties::instance()->getInt("SHIP_LIFES");
		_asteroidsLeft = 0;
		_currentScore = 0;
		_cooldownLeft = 0;
		_cooldownPeriod = false;
		_levelRunning = false;
		_difficulty = cg::Properties::instance()->getDouble("DIFFICULTY");
		_frameRate = 0;
		_maxFrameRateAccul = cg::Properties::instance()->getDouble("SHOW_FPS"); 
		_showFrameRate = (_maxFrameRateAccul > 0) ? true : false;
		_frameRateAccul = 0;
		_frameRateAcculDivider = 0;
	}
	GameManager::~GameManager() {
	}
	
	void GameManager::createEntities() {
		changeLevel(0);
		beginLevel();
	}

	void GameManager::postInit() {
		_radarSize = cg::Properties::instance()->getDouble("RADAR_SIZE");
		_shipsLeft = cg::Properties::instance()->getInt("SHIP_LIFES");
		_cooldownTime = cg::Properties::instance()->getDouble("COOLDOWN_TIME");
	}
	

	void GameManager::resetGame() {
		_levelRunning = false;
		_shipsLeft = cg::Properties::instance()->getInt("SHIP_LIFES");
		
		//make sure we have a clean slate - no new particles are going to be added
		//and we dont want duplicates in the deleted ones
		_newParticles.clear();
		_deletedParticles.clear();
		
		std::vector<Particle *> particles = getParticles();
		for(std::vector<Particle*>::size_type i = 0; i < particles.size(); i++) {
			//cant use this because asteroids would generate new ones
			//particles[i]->destroy();
			destroyParticle(particles[i]->getId());
		}
		_application->getExplosionManager()->clearExplosions();
		changeLevel(0);
		setScore(0);
	}

	void GameManager::addParticle(Particle * p) {
		if(p->getParticleType() == 'a') {
			_asteroidsLeft++;
		}
		ParticleManager::addParticle(p);
	}

	void GameManager::preUpdate(unsigned long elapsed_millis) {
		ParticleManager::preUpdate(elapsed_millis);
		if(_asteroidsLeft == 0 && _levelRunning) {
			if(_currentLevel == 0)  {
				finishLevel();
			} else if( ! _cooldownPeriod) {
				_cooldownPeriod = true;
				_cooldownLeft = _cooldownTime;
			} else {
				_cooldownLeft -= elapsed_millis/1000.0;
				if(_cooldownLeft <= 0) {
					finishLevel();
				}
			}
		}
		_frameRateAccul+= elapsed_millis/1000.0;
		_frameRateAcculDivider++;
		if(_maxFrameRateAccul > 0 && _frameRateAccul > _maxFrameRateAccul) {
			_frameRate = 1000.0/(_frameRateAccul/(_frameRateAcculDivider/1000.0));
			_frameRateAccul = 0;
			_frameRateAcculDivider = 0;
		}
	}

	void GameManager::destroyParticle(std::string id) {
		Particle * destroyedParticle = getParticle(id);
		char pType = destroyedParticle->getParticleType();
		
		switch(pType) {
			case 'a':
				if(_levelRunning) {
					addScore(destroyedParticle->getMass()/10);
				}
				--_asteroidsLeft;
				break;
			case 's':
				if(_levelRunning) {
					addScore(-1000);
					if (_shipsLeft > 0) {
						_shipsLeft--;
						createShip(); 
					} else {
						//_levelRunning = false;
						GameOverState::instance()->changeTo(_application);
					}
				}
				break;
		}
		_application->getExplosionManager()->generateExplosion(destroyedParticle);
		ParticleManager::destroyParticle(id);
	}
	void GameManager::createLaserShot(cg::Vector2d position, double radiansRotation, cg::Vector2d velocity, double degreesRotation) {
		if(_levelRunning) {
			addScore(-100);
			ParticleManager::createLaserShot(position, radiansRotation, velocity, degreesRotation);
		}
	}
	void GameManager::beginLevel() {
		if(_currentLevel == 0) { //level 0 = demo level
			_asteroidsLeft = 0;
			createAsteroids(cg::Properties::instance()->getInt("DEMO_ASTEROIDS"));
			return;
		}
		_asteroidsLeft = 0;
		createShip();
		double scale = 2*_difficulty*log10((double)((_currentLevel%10+1)*_difficulty+2)) + 1.2*pow(_difficulty*_currentLevel/10, 2);
		double delta = _difficulty*log10((double)(_currentLevel%10+1))/(_currentLevel%10+1)+0.5;
		unsigned int asteroids = abs(2*_difficulty*log10((double)((_currentLevel%10+1)+1))+(_currentLevel%10+1)*0.1+0.5);
		createAsteroids(asteroids, scale, delta);
		_levelRunning = true;
		_cooldownPeriod = false;
	}
	void GameManager::finishLevel() {
		_levelRunning = false;
		_cooldownPeriod = false;
		//make sure we have a clean slate - no new particles are going to be added
		//and we dont want duplicates in the deleted ones
		_newParticles.clear();
		_deletedParticles.clear();
		
		std::vector<Particle *> particles = getParticles();
		for(std::vector<Particle*>::size_type i = 0; i < particles.size(); i++) {
			//cant use this because asteroids would generate new ones
			//particles[i]->destroy();
			destroyParticle(particles[i]->getId());
		}
		_asteroidsLeft = 0; //lets just make sure
		_application->getExplosionManager()->clearExplosions();
		if(_currentLevel != 0) {
			if((_currentLevel%3) == 0) {
				_shipsLeft++;
			}
			EndOfLevelState::instance()->changeTo(_application);
		}
	}
	
	void GameManager::advanceLevel() {
		_currentLevel++;
	}

	void GameManager::changeLevel(unsigned int level) {
		_currentLevel = level;
	}
	unsigned int GameManager::getCurrentLevel() {
		return _currentLevel;
	}
	int GameManager::getCurrentScore() {
		return _currentScore;
	}
	void GameManager::setScore(int score) {
		_currentScore = score;
	}
	void GameManager::addScore(int score) {
		_currentScore += score;
	}

	void GameManager::preDrawOverlay() {
		std::ostringstream score;
		score << "Score: " << getCurrentScore();
		std::ostringstream shipsLeft;
		shipsLeft << "Ships: " << _shipsLeft;
		std::ostringstream currLevel;
		currLevel << "Level " << _currentLevel;
		std::ostringstream frameRate;


		
		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		glPushMatrix();
		{
			glColor4d(0.9, 0, 0, 0.3);
			glBegin(GL_QUADS);
			{
				glVertex3d(win.width-win.width/_radarSize, 0, 0);
				glVertex3d(win.width-win.width/_radarSize, win.height/_radarSize + 15, 0);
				glVertex3d(win.width, win.height/_radarSize + 15, 0);
				glVertex3d(win.width, 0, 0);
			}
			glEnd();
		}
		glPopMatrix();	

		cg::Util::instance()->drawStrokeString(currLevel.str(), 10 , win.height-25, 0.15, false, 2, 0.5, 0, 0.25, 1);
		cg::Util::instance()->drawStrokeString(shipsLeft.str(), 10 , 35, 0.2, false, 2, 0, 0.5, 0.25, 1);
		cg::Util::instance()->drawStrokeString(score.str(), 10 , 10, 0.2, false, 2, 0, 0.25, 0.5, 1);
		
		if(_showFrameRate) {
			frameRate << int(_frameRate+0.5);
			cg::Util::instance()->drawStrokeString(frameRate.str(), win.width - 25 , win.height-25, 0.1, false, 2, 1, 1, 0, 1);
		}
		glPopAttrib();
	}

}