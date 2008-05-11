#ifndef LASERSHOT_H
#define LASERSHOT_H

#include <string>
#include <vector>
#include "cg/cg.h"
#include <cmath>
#include "Particle.h"
#include "ParticleManager.h"
#include "SpaceShip.h"


namespace asteroids {
	class ParticleManager;

	class LaserShot : public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener,
		public Particle
	{
	private:
		double _secondsToLive, _radius;
		
	public:
		LaserShot(std::string id, ParticleManager * particleManager);
		~LaserShot();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void onReshape(int width, int height);
		bool collidesWith(PhysicsObject *pobject);
	};
}

#endif
