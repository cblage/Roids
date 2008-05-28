#pragma once
#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H
#pragma message("SpaceShip is included")

#include <string>
#include "cg/cg.h"
#include <cmath>
#include "Particle.h"
#include "PhysicsObject.h"
#include "SpaceShipHyperAccelerator.h"
#include "ShipController.h"
#include <sstream>
#include <string>


namespace asteroids {
	class ParticleManager;
	class SpaceShipHyperAccelerator;
	class ShipController;

	class SpaceShip : public cg::IDrawListener,
		public cg::IUpdateListener, 
		public cg::IReshapeEventListener,
		public Particle
	{
	private:
		std::string _message;
		cg::Vector2d _size;
		double _winWidth, _winHeight, _charlesBronsonKilledSecondsAgo;		
		SpaceShipHyperAccelerator * _hyperAccelerator;
		int _charlesBronsonStyle, _maxCharlesBronsonStyle;
		ShipController * _controller;
		double _radarSize;
	public:
		SpaceShip(std::string id, ParticleManager *  particleManager);
		SpaceShip(std::string id, ParticleManager *  particleManager, int lifes);
		~SpaceShip();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void onReshape(int width, int height);
		void hyperAccelerate(void);
		void shootLaser(void);
		void onKeyPressed(unsigned char key);
		void onKeyReleased(unsigned char key);
		void drawOverlay();
	};
}

#endif