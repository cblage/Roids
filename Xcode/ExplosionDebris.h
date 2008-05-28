#pragma once
#ifndef EXPLOSIONDEBRIS_H
#define EXPLOSIONDEBRIS_H
#pragma message("ExplosionDebris is included")

#include <string>
#include <vector>
#include "cg/cg.h"
#include <cmath>
#include "Particle.h"


namespace asteroids {
	class ParticleManager;
	class SpaceShip;
	class PhysicsObject;
	class Particle;

	class ExplosionDebris : public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener,
		public Particle
	{
	private:
		double _maxSecondsToLive, _secondsToLive, _radius, _alpha;
		cg::Vector3d _color;
		
	public:
		ExplosionDebris(std::string id, ParticleManager * particleManager, cg::Vector3d color = cg::Vector3d(0.7, 0.7, 0.7));
		~ExplosionDebris();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void onReshape(int width, int height);
		bool collidesWith(PhysicsObject *pobject);
		double randomBetween(double min, double max);
	};
}

#endif
