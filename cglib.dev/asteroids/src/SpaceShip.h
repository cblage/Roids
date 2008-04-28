#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H

#include <string>
#include "cg/cg.h"
#include <cmath>
#include "SpaceShipAccelerator.h"
#include "SpaceShipRotator.h"
#include "SpaceShipHyperAccelerator.h"
#include "CollidableObject.h"

namespace asteroids {
	class SpaceShip : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener,
		public cg::IDrawOverlayListener,
		public CollidableObject
	{
	private:
		cg::Vector2d _position, _size;
		cg::Vector2d _velocity;
		double _winWidth, _winHeight;		
		SpaceShipAccelerator *_accelerator;
		SpaceShipRotator * _rotator;
		SpaceShipHyperAccelerator * _hyperAccelerator;
	public:
		SpaceShip(std::string id);
		~SpaceShip();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void drawOverlay();
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
		void hyperAccelerate(void);
	};
}

#endif