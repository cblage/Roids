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
		addEntity(ship);
		addEntity(new SpaceShipController(ship));
	}
}