#include "MyApp.h"

namespace asteroids {

	MyApp::MyApp() : cg::Application("config.ini") {
		_window.caption = "Les Asteroids";
		_window.width = 800;
		_window.height = 600;
		_state = NULL;
	}
	MyApp::~MyApp() {
		delete(_screenManager);
	}
	void MyApp::createEntities() {
		_screenManager = new ScreenManager();
		BeforeGameState::instance()->changeTo(this);

		addEntity(new ApplicationController(this));
		addEntity (new MyCamera());
		addEntity(new StarSphere());
		addEntity(_screenManager);
		addEntity(new ParticleManager("Particle Manager"));
		addEntity(new Lights());
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

}