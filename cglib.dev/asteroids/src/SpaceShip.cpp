#include "SpaceShip.h"

namespace asteroids {

	SpaceShip::SpaceShip(std::string id) : cg::Entity(id) {
		_accelerator = new SpaceShipAccelerator(this);
		_rotator = new SpaceShipRotator(this);
		_hyperAccelerator = new SpaceShipHyperAccelerator(this);
	}
	SpaceShip::~SpaceShip() {
		delete(_accelerator);
		delete(_rotator);
		delete(_hyperAccelerator);
	}

	void SpaceShip::init() {
		// Read from property file
		_size = cg::Vector2d(
								cg::Properties::instance()->getDouble("SHIP_LENGTH"),
								cg::Properties::instance()->getDouble("SHIP_HEIGHT")
							);

		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_velocity = cg::Vector2d(0, 0);
		_position = cg::Vector2d(_winWidth/2, _winHeight/2);
	}
	void SpaceShip::update(unsigned long elapsed_millis) {
		double elapsed_seconds = elapsed_millis / 1000.0;
		
		_hyperAccelerator->update(elapsed_seconds);
		_rotator->update(elapsed_seconds);
		_accelerator->update(elapsed_seconds);

		_position += _velocity * elapsed_seconds;

		if(_position[0] < 0) { 
			_position[0] = _winWidth;
		}
		if(_position[0] > _winWidth) { 
			_position[0] = 0;
			}
		if(_position[1] < 0) { 
			_position[1] = _winHeight;
		}
		if(_position[1] > _winHeight) { 
			_position[1] = 0;
		}
	}
	void SpaceShip::draw() {
		cg::Vector3d tip = cg::Vector3d(_size[0], 0, 0)/2.0;
		cg::Vector3d backTip = cg::Vector3d(-_size[0], 0, 0) / 1.5;
		cg::Vector3d topLeftCorner = cg::Vector3d(-_size[0], -_size[1], _size[1])/2.0;
		cg::Vector3d topRightCorner = cg::Vector3d(-_size[0], _size[1], _size[1])/2.0;
		cg::Vector3d bottomLeftCorner = cg::Vector3d(-_size[0], -_size[1], -_size[1])/2.0;
		cg::Vector3d bottomRightCorner = cg::Vector3d(-_size[0], _size[1], -_size[1])/2.0;
		
		glPushMatrix();
			glTranslated(_position[0], _position[1], 0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glRotated(getRotation(true), 0, 0, 1);
			glColor3d(0.5,0.9,0.5);
			glLineWidth(1.5);
			glBegin(GL_POLYGON);
				glVertex3d(tip[0], tip[1], tip[2]);
				glVertex3d(topLeftCorner[0], topLeftCorner[1], topLeftCorner[2]);
				glVertex3d(topRightCorner[0], topRightCorner[1], topRightCorner[2]);
				glVertex3d(bottomLeftCorner[0], bottomLeftCorner[1], bottomLeftCorner[2]);
				glVertex3d(bottomRightCorner[0], bottomRightCorner[1], bottomRightCorner[2]);
			glEnd();
			glPopMatrix();
		glFlush();
	}
	void SpaceShip::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}

	void SpaceShip::accelerate(double factor, bool withRotation) {	
		_accelerator->accelerate(factor, withRotation);
	}

	void SpaceShip::accelerate(double factor, bool withRotation, cg::Vector2d minVelocity) {	
		_accelerator->accelerate(factor, withRotation, minVelocity);
	}
	
	void SpaceShip::startAcceleration(double factor, bool withRotation) {
		_accelerator->start(factor, withRotation);
	}
	void SpaceShip::startAcceleration(double factor, bool withRotation, cg::Vector2d minVelocity) {
		_accelerator->start(factor, withRotation, minVelocity);
	}

	void SpaceShip::stopAcceleration() {
		_accelerator->stop();
	}



	void SpaceShip::startRotation(double factor) {
		_rotator->start(factor);
	}

	void SpaceShip::stopRotation() {
		_rotator->stop();
	}
	
	
	void SpaceShip::setVelocity(cg::Vector2d velocity) {
		_velocity = velocity;
	}

	cg::Vector2d SpaceShip::getVelocity() const {
		return _velocity;
	}


	cg::Vector2d SpaceShip::getNormalizedVelocity() const {
		if(_velocity == cg::Vector2d(0,0)) 
			return cg::Vector2d(0,0);

		return _velocity / sqrt(pow(_velocity[0], 2) + pow(_velocity[1], 2));
	}

	void SpaceShip::drawOverlay() {
		glColor3d(0.9,0.1,0.1);
		std::ostringstream os;
		os << "acceleration: " << _accelerator->getAcceleration() << " velocity: " << _velocity  << " rotation angle: " << _rotator->getRotation(true) << " or " << _rotator->getRotation() << " sin(): " << sin( _rotator->getRotation()) << " cos(): " << cos(_rotator->getRotation());
		cg::Util::instance()->drawBitmapString(os.str(), 10,10);
	}

	double SpaceShip::getRotation() const {
		return _rotator->getRotation();
	}
	double SpaceShip::getRotation(bool inDegrees) const{
		return _rotator->getRotation(inDegrees);
	}
	cg::Vector2d SpaceShip::getUniverseDimensions(void) {
		return cg::Vector2d(_winWidth, _winHeight);
	}
	void SpaceShip::setPosition(cg::Vector2d position) {
		_position = position;
	}
	void SpaceShip::hyperAccelerate(void) {
		_hyperAccelerator->hyperAccelerate();
	}
}