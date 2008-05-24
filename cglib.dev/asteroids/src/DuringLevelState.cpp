#include "DuringLevelState.h"

namespace asteroids {

	SINGLETON_IMPLEMENTATION(DuringLevelState)
	
	void DuringLevelState::enter() {
		_application->getGameManager()->beginLevel();
	}
	std::string DuringLevelState::getName(void) {
		return "DuringLevelState";
	}

}
