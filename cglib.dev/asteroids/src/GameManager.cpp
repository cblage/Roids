#include "GameManager.h"

namespace asteroids {
	GameManager::GameManager(std::string id, MyApp *application) : ParticleManager(id), _application(application) {
		_shipsLeft = cg::Properties::instance()->getInt("SHIP_LIFES");
		_asteroidsLeft = 0;
		_currentScore = 0;
		_levelRunning = false;
	}
	GameManager::~GameManager() {
	}
	
	void GameManager::createEntities() {
		changeLevel(0);
		beginLevel();
	}
	

	void GameManager::resetGame() {
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
			finishLevel();
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
					}
				}
				break;
		}
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
			createAsteroids(cg::Properties::instance()->getInt("DEMO_ASTEROIDS"));
			return;
		}
		createShip();
		createAsteroids((int)pow(log((double)_currentLevel*2+2),2));
		_levelRunning = true;
	}
	void GameManager::finishLevel() {
		_levelRunning = false;
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

		if(_currentLevel != 0) {
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

		GLboolean lightingEnabled;
		lightingEnabled = glIsEnabled(GL_LIGHTING);
		if(lightingEnabled == GL_TRUE) glDisable(GL_LIGHTING);

		cg::Util::instance()->drawStrokeString(shipsLeft.str(), 10 , 35, 0.2, false, 2, 0, 0.5, 0.25, 1);
		cg::Util::instance()->drawStrokeString(score.str(), 10 , 10, 0.2, false, 2, 0, 0.25, 0.5, 1);

		if(lightingEnabled == GL_TRUE) glEnable(GL_LIGHTING);
	}


}