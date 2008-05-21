#include "MyApp.h"

namespace asteroids {

	MyApp::MyApp() : cg::Application("config.ini") {
		_window.caption = "Les Asteroids";
		_window.width = 800;
		_window.height = 600;
	}
	MyApp::~MyApp() {
	}
	void MyApp::createEntities() {
		addEntity (new MyCamera());
		addEntity(new StarSphere());
		ParticleManager *particleManager = new ParticleManager("Particle Manager");
		addEntity(particleManager);
		addEntity(new Lights());
	}
}