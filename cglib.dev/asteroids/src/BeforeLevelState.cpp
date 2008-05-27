#include "BeforeLevelState.h"

namespace asteroids {

	SINGLETON_IMPLEMENTATION(BeforeLevelState)
	
	void BeforeLevelState::enter() {
		_warmupTime = cg::Properties::instance()->getDouble("WARMUP_TIME");
		_posWarmupTime = cg::Properties::instance()->getDouble("POS_WARMUP_TIME");
		_timeLeft = _posWarmupTime+_warmupTime + cg::Properties::instance()->getDouble("PRE_WARMUP_TIME");
		_screen = new Screen("BeforeLevelScreen");
		_screen->init();
		_screen->setMessage(getMessage());
		_application->addScreen(_screen);
	}

	void BeforeLevelState::resume(MyApp * application) {
		ApplicationState * s = getPreviousState();
		changeState(application, this);
		setPreviousState(s);
		_screen->setMessage(getMessage());
		_application->addScreen(_screen);
	}
	
	void BeforeLevelState::suspend() {
		_application->removeScreen(_screen);
		//delete(_screen);
	}
	

	void BeforeLevelState::leave() {
		_application->removeScreen(_screen);
		delete(_screen);
	}

	std::string BeforeLevelState::getMessage() {
		std::ostringstream os;
		if(_timeLeft > _warmupTime+_posWarmupTime) {
			os << "Level " << _application->getGameManager()->getCurrentLevel();
			return os.str();
		} else if(_timeLeft > _posWarmupTime) {
			os << ceil(_timeLeft-_posWarmupTime);
			return os.str();
		}
		os << "Go!";
		return os.str();
	}
	
	void BeforeLevelState::update(unsigned long elapsed_millis) {
		_timeLeft -= elapsed_millis/1000.0;
		_screen->setMessage(getMessage());
		if(_timeLeft < 0) {
			DuringLevelState::instance()->changeTo(_application);
		}
	}

	std::string BeforeLevelState::getName(void) {
		return "BeforeLevelState";
	}

}
