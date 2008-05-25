#include "DuringLevelState.h"

namespace asteroids {

	SINGLETON_IMPLEMENTATION(DuringLevelState)
	
	void DuringLevelState::enter() {
		_application->getGameManager()->beginLevel();
	}
	void DuringLevelState::resume(MyApp * application) {
		changeState(application, this);
	}

	std::string DuringLevelState::getName(void) {
		return "DuringLevelState";
	}

}
