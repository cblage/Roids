#include "ScreenManager.h"

namespace asteroids {

	ScreenManager::ScreenManager() : cg::Group("ScreenManager") {
	}
	ScreenManager::~ScreenManager() {
	}
	void ScreenManager::createEntities() {
		//add(new Screen("InitScreen"));
	}

	void ScreenManager::addScreen(Screen * s) {
		add(s);
	}
	
	void ScreenManager::removeScreen(Screen * s) {
		remove(s->getId());
	}
}