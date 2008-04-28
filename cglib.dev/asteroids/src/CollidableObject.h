#ifndef COLLIDABLE_OBJECT_H
#define COLLIDABLE_OBJECT_H

#include "cg/cg.h"

namespace asteroids {	
	class CollidableObject
	{
	public:
		virtual ~CollidableObject(void);
		virtual bool collidesWith(CollidableObject *collidable);
	protected:
		double getCollisionRadius();
		cg::Vector2d getCollisionCenter();
		void setCollisionRadius(double collisionRadius);
		void setCollisionCenter(cg::Vector2d collisionCenter);
	

	private:
		double _collisionRadius;
		cg::Vector2d _collisionCenter;
	};
}

#endif