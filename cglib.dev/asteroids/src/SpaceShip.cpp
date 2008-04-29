#include "SpaceShip.h"

namespace asteroids {

	SpaceShip::SpaceShip(std::string id) : cg::Entity(id) {
		_physics = new PhysicsEngine();
		_hyperAccelerator = new SpaceShipHyperAccelerator(this);
	}
	SpaceShip::~SpaceShip() {
		delete(_physics);
		delete(_hyperAccelerator);
	}

	void SpaceShip::init() {
		// Read from property file
		_size = cg::Vector2d(
								cg::Properties::instance()->getDouble("SHIP_LENGTH"),
								cg::Properties::instance()->getDouble("SHIP_HEIGHT")
							);

		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth=win.width;
		_winHeight=win.height;
		
		//DESCOMENTAR LINHA ABAIXO
		
		_physics->setUniverseDimensions(win.width,win.height);
		setCollisionRadius(_size[0]);
		_physics->setVelocity(cg::Vector2d(0, 0));
		_physics->setPosition(cg::Vector2d(_winWidth/2, _winHeight/2));
		setCollisionCenter(getPosition());
	}
	void SpaceShip::update(unsigned long elapsed_millis) {
		double elapsed_seconds = elapsed_millis / 1000.0;
		
		_hyperAccelerator->update(elapsed_seconds);
		_physics->update(elapsed_millis);
		setCollisionCenter(getPosition());
	}
	void SpaceShip::draw() {
		cg::Vector3d tip = cg::Vector3d(_size[0], 0, 0)/2.0;
		cg::Vector3d backTip = cg::Vector3d(-_size[0], 0, 0) / 1.5;
		cg::Vector3d topLeftCorner = cg::Vector3d(-_size[0], -_size[1], _size[1])/2.0;
		cg::Vector3d topRightCorner = cg::Vector3d(-_size[0], _size[1], _size[1])/2.0;
		cg::Vector3d bottomLeftCorner = cg::Vector3d(-_size[0], -_size[1], -_size[1])/2.0;
		cg::Vector3d bottomRightCorner = cg::Vector3d(-_size[0], _size[1], -_size[1])/2.0;
		
		cg::Vector2d position = getPosition();
		
		glPushMatrix();
		{
			glTranslated(position[0], position[1], 0);
			glRotated(getRotation(true), 0, 0, 1);
			glColor3d(0.5,0.9,0.5);
			//top face
			glBegin(GL_POLYGON);
			{
				//glColor3d(1,0, 0);
				glVertex3d(tip[0], tip[1], tip[2]);
				glVertex3d(topLeftCorner[0], topLeftCorner[1], topLeftCorner[2]);
				glVertex3d(topRightCorner[0], topRightCorner[1], topRightCorner[2]);
			}
			glEnd();

			//bottom face
			glBegin(GL_POLYGON);
			{
				//glColor3d(0, 1, 0);
				glVertex3d(tip[0], tip[1], tip[2]);
				glVertex3d(bottomLeftCorner[0], bottomLeftCorner[1], bottomLeftCorner[2]);
				glVertex3d(bottomRightCorner[0], bottomRightCorner[1], bottomRightCorner[2]);
			}
			glEnd();

			//right face
			glBegin(GL_POLYGON);
			{
				//glColor3d(0 ,0, 1);
				glVertex3d(tip[0], tip[1], tip[2]);
				glVertex3d(topRightCorner[0], topRightCorner[1], topRightCorner[2]);
				glVertex3d(bottomRightCorner[0], bottomRightCorner[1], bottomRightCorner[2]);
			}
			glEnd();
			
			//left face
			glBegin(GL_POLYGON);
			{
				//glColor3d(1,1, 0);
				glVertex3d(tip[0], tip[1], tip[2]);
				glVertex3d(topLeftCorner[0], topLeftCorner[1], topLeftCorner[2]);
				glVertex3d(bottomLeftCorner[0], bottomLeftCorner[1], bottomLeftCorner[2]);				
			}
			glEnd();

			//bottom
			glBegin(GL_POLYGON);
			{
				//glColor3d(0,1, 1);
				glVertex3d(topLeftCorner[0], topLeftCorner[1], topLeftCorner[2]);
				glVertex3d(topRightCorner[0], topRightCorner[1], topRightCorner[2]);
				glVertex3d(bottomLeftCorner[0], bottomLeftCorner[1], bottomLeftCorner[2]);
				glVertex3d(bottomRightCorner[0], bottomRightCorner[1], bottomRightCorner[2]);
			}
			glEnd();
		}
		glPopMatrix();
		glFlush();
	}
	void SpaceShip::onReshape(int width, int height) {

		//DESCOMENTAR LINHA ABAIXO
		
		_winWidth = width;
		_winHeight = height;
		_physics->setUniverseDimensions(width,height);
	}

	void SpaceShip::accelerate(double factor, bool withRotation) {	
		_physics->accelerate(factor, withRotation);
	}

	void SpaceShip::accelerate(double factor, bool withRotation, cg::Vector2d minVelocity) {	
		_physics->accelerate(factor, withRotation, minVelocity);
	}
	
	void SpaceShip::startAcceleration(double factor, bool withRotation) {
		_physics->startAcceleration(factor, withRotation);
	}
	void SpaceShip::startAcceleration(double factor, bool withRotation, cg::Vector2d minVelocity) {
		_physics->startAcceleration(factor, withRotation, minVelocity);
	}

	void SpaceShip::stopAcceleration() {
		_physics->stopAcceleration();
	}

	void SpaceShip::startRotation(double factor) {
		_physics->startRotator(factor);
	}

	void SpaceShip::stopRotation() {
		_physics->stopRotator();
	}
	
	
	void SpaceShip::setVelocity(cg::Vector2d velocity) {
		_physics->setVelocity(velocity);
	}

	cg::Vector2d SpaceShip::getVelocity() const {
		return _physics->getVelocity();
	}


	cg::Vector2d SpaceShip::getNormalizedVelocity() const {
		return _physics->getNormalizedVelocity();
	}

	void SpaceShip::drawOverlay() {
		glColor3d(0.9,0.1,0.1);
		std::ostringstream os;
		os << "acceleration: " << getAcceleration() << " velocity: " << getVelocity()  << " rotation angle: " << getRotation(true) << " or " << getRotation() << " position: " << getPosition();
		cg::Util::instance()->drawBitmapString(os.str(), 10,10);
	}

	cg::Vector2d SpaceShip::getAcceleration() const {
		return _physics->getAcceleration();
	}

	double SpaceShip::getRotation() const {
		return _physics->getRotation();
	}

	double SpaceShip::getRotation(bool inDegrees) const{
		return _physics->getRotation(inDegrees);
	}
	cg::Vector2d SpaceShip::getUniverseDimensions(void) {
		return cg::Vector2d(_winWidth, _winHeight);
	}
	void SpaceShip::setPosition(cg::Vector2d position) {
		_physics->setPosition(position);
	}
	void SpaceShip::hyperAccelerate(void) {
		_hyperAccelerator->hyperAccelerate();
	}
	cg::Vector2d SpaceShip::getPosition() const {
		return _physics->getPosition();
	}
}