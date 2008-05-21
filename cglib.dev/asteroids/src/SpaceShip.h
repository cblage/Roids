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



namespace asteroids {
	class ParticleManager;
	class SpaceShipHyperAccelerator;
	class ShipController;

	class SpaceShip : public cg::IDrawListener,
		public cg::IUpdateListener,
		public Particle
	{
	private:
		cg::Vector2d _size;
		double _winWidth, _winHeight, _charlesBronsonKilledSecondsAgo;		
		SpaceShipHyperAccelerator * _hyperAccelerator;
		int _charlesBronsonStyle;
		ShipController * _controller;
	public:
		SpaceShip(std::string id, ParticleManager *  particleManager);
		~SpaceShip();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void onReshape(int width, int height);
		void hyperAccelerate(void);
		void shootLaser(void);
		void onKeyPressed(unsigned char key);
		void onKeyReleased(unsigned char key);
	};
}

#endif