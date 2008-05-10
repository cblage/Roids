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
		//addEntity(new MyCamera());
		
		MyCamera *camera = new MyCamera();
		addEntity (camera);
		addEntity(new StarSphere());
		SpaceShip *ship = new SpaceShip("Le Ship");
		ParticleManager *particleManager = new ParticleManager("Particle Manager", ship);
		ship->setParticleManager(particleManager);

		addEntity(ship);
		addEntity(new GameController(ship,camera));
		addEntity(particleManager);
	}
}