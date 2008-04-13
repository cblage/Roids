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
		SpaceShip *ship = new SpaceShip("Le Ship");
	
		addEntity(new MyCamera());
		addEntity(new StarSphere());
		addEntity(ship);
		addEntity(new SpaceShipController(ship));
		addEntity(new Asteroid("ast1", 2));
		addEntity(new Asteroid("ast2", 1));
		addEntity(new Asteroid("ast3", 3));
	}
}