#ifndef ASTEROID_H
#define ASTEROID_H

#include <string>
#include <vector>
#include "cg/cg.h"
#include <cmath>
#include "Particle.h"
#include "ParticleManager.h"
#include "SpaceShip.h"
#include "PhysicsObject.h"
#include "PhysicsEngine.h"

namespace asteroids {
	class ParticleManager;

	class Asteroid : public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener,
		public Particle,
		public PhysicsObject
	{
	private:
		std::vector<cg::Vector3d> _asteroid_vector, _asteroid_vector2;
		cg::Vector2d _size;
		double _scaleFactor, _radius;

		
	public:
		Asteroid(std::string id, ParticleManager * particleManager);
		Asteroid(std::string id, double scaleFactor, ParticleManager * particleManager);
		~Asteroid();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void onReshape(int width, int height);
		double randomBetween(double min, double max);
		bool collidesWith(PhysicsObject *pobject);
	};
}

#endif
