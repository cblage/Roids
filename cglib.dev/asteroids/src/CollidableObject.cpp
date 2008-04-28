#include "CollidableObject.h"


namespace asteroids {	

	CollidableObject::~CollidableObject() {}
	
	double CollidableObject::getCollisionRadius() { 
		return _collisionRadius;
	}
	cg::Vector2d CollidableObject::getCollisionCenter() { 
		return _collisionCenter;
	}
	void CollidableObject::setCollisionRadius(double collisionRadius) { 
		_collisionRadius = collisionRadius;
	}
	void CollidableObject::setCollisionCenter(cg::Vector2d collisionCenter) {
		_collisionCenter = collisionCenter;
	}
	bool CollidableObject::collidesWith(CollidableObject *collidable) {
		return (length(collidable->getCollisionCenter() - getCollisionCenter()) <= collidable->getCollisionRadius() + getCollisionRadius());
	}
}