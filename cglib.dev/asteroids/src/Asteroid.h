#ifndef ASTEROID_H
#define ASTEROID_H

#include <string>
#include <vector>
#include "cg/cg.h"
#include <cmath>
#include "AsteroidAccelerator.h"
#include "AsteroidRotator.h"


namespace asteroids {
	class Asteroid : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener
	{
	private:
		std::vector<cg::Vector3d> _asteroid_vector;
		cg::Vector2d _position, _size;
		cg::Vector2d _velocity;
		double _winWidth, _winHeight, _scaleFactor;		
		AsteroidAccelerator *_accelerator;
		AsteroidRotator * _rotator;
		
	public:
		Asteroid(std::string id, double scaleFactor);
		~Asteroid();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
        void onReshape(int width, int height);
		void accelerate(double factor, bool withRotation);
		void accelerate(double factor, bool withRotation, cg::Vector2d minVelocity);
		void rotate(double factor);
		void startRotation(double factor);
		void stopRotation();
		void startAcceleration(double factor, bool withRotation);
		void startAcceleration(double factor, bool withRotation, cg::Vector2d minVelocity);
		void stopAcceleration();
		void setVelocity(cg::Vector2d velocity);
		cg::Vector2d getNormalizedVelocity() const;
		cg::Vector2d getVelocity() const;
		double getRotation() const;
		double getRotation(bool inDegrees) const;
		cg::Vector2d getUniverseDimensions(void);
		void setPosition(cg::Vector2d position);
double randomBetween(double min, double max);
	};
}

#endif