#include "MyApp.h"

namespace asteroids {

	MyApp::MyApp() : cg::Application("config.ini") {
		_window.caption = "Roids! (Alpha Version)";
		_window.width = 800;
		_window.height = 600;
		_state = NULL;
		_gameManager = NULL;
		_screenManager = NULL;
		_explosionManager = NULL;
	}
	MyApp::~MyApp() {
	}
	void MyApp::createEntities() {
		_screenManager = new ScreenManager();
		_gameManager = new GameManager("GameManager", this);
		_explosionManager = new ExplosionManager("ExplosionManager", this);
		BeforeGameState::instance()->changeTo(this);
		addEntity(new ApplicationController(this));
		addEntity (new MyCamera());
		addEntity(new StarSphere());
		addEntity(_explosionManager);
		addEntity(_gameManager);
		addEntity(new Lights());
		addEntity(_screenManager);
	}

	void MyApp::changeState(ApplicationState * state) {
		if(state != _state) {
			_state = state;
		}
	}
	ApplicationState * MyApp::getState() {
		return _state;
	}

	void MyApp::onUpdate() {
		_state->onUpdate();
		_state->update(_time.elapsed);
	}
	void MyApp::onDisplay() {
		_state->onDisplay();
	}

	void MyApp::onKeyPressed(unsigned char key) {
		_state->onKeyPressed(key);
	}
	void MyApp::pause() {
		_state->pause();
	}
	void MyApp::quit() {
		_state->quit();
	}
	void MyApp::addScreen(Screen * s) {
		_screenManager->addScreen(s);
	}
	
	void MyApp::removeScreen(Screen * s) {
		_screenManager->removeScreen(s);
	}

	GameManager * MyApp::getGameManager() {
		return _gameManager;
	}
	ExplosionManager * MyApp::getExplosionManager() {
		return _explosionManager;
	}
	void MyApp::resetTime() {
		updateFrameTime();
	}
}