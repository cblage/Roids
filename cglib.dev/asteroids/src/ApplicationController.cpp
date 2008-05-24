#include "ApplicationController.h"

namespace asteroids {

	ApplicationController::ApplicationController(MyApp* application) : cg::Entity("AppController"), _application(application) {
	}
	ApplicationController::~ApplicationController() {
	}
	
	void ApplicationController::init() {
	}
	
	void ApplicationController::onKeyPressed(unsigned char key) {
		_application->onKeyPressed(key);
	}
	void ApplicationController::onKeyReleased(unsigned char key) {
	}
	void ApplicationController::onSpecialKeyPressed(int key) {
	}
	void ApplicationController::onSpecialKeyReleased(int key) {
	}

}
