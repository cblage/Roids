#include "SpaceShip.h"

namespace asteroids {

	SpaceShip::SpaceShip(std::string id, ParticleManager *  particleManager) : Particle(id, particleManager, 's') {
		_hyperAccelerator = new SpaceShipHyperAccelerator(this);
		_controller = new ShipController(this);
		setMass(cg::Properties::instance()->getDouble("SHIP_MASS"));
		initHealth(cg::Properties::instance()->getDouble("SHIP_HEALTH"));
		
		
	}

	SpaceShip::~SpaceShip() {
		delete(_hyperAccelerator);
	}

	void SpaceShip::init() {
		// Read from property file
		_radarSize = cg::Properties::instance()->getDouble("RADAR_SIZE");
		_radarAdvanced = cg::Properties::instance()->getInt("RADAR_ADVANCED");
		
		_invulTimeMax = cg::Properties::instance()->getDouble("SHIP_RESPAWN_INVUL");
		_invulTime = _invulTimeMax;

		_size = cg::Vector2d(
								cg::Properties::instance()->getDouble("SHIP_LENGTH"),
								cg::Properties::instance()->getDouble("SHIP_HEIGHT")
							);

		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		setUniverseDimensions(win.width,win.height);
		setCollisionRadius(_size[1]/2);
		setVelocity(cg::Vector2d(0, 0));
		setPosition(cg::Vector2d(win.width/2, win.height/2));
		setCollisionCenter(getPosition());
		_maxCharlesBronsonStyle = cg::Properties::instance()->getDouble("SHIP_SHOTS");
		_charlesBronsonStyle = _maxCharlesBronsonStyle;
		_charlesBronsonKilledSecondsAgo = 0;
		
	}
	void SpaceShip::update(unsigned long elapsed_millis) {
		PhysicsObject::update(elapsed_millis);
		double elapsed_seconds = elapsed_millis / 1000.0;	
		accelerate(-50*elapsed_seconds, false, cg::Vector2d(0, 0));
		_hyperAccelerator->update(elapsed_seconds);
		cg::Vector2d position = getPosition();
		_charlesBronsonKilledSecondsAgo = _charlesBronsonKilledSecondsAgo + elapsed_seconds;
		if (_charlesBronsonKilledSecondsAgo >= 1) {
			if (_charlesBronsonStyle >= _maxCharlesBronsonStyle){
				_charlesBronsonKilledSecondsAgo--;
				return;
			}else {
				_charlesBronsonStyle++;
				_charlesBronsonKilledSecondsAgo--;
			}
		}
		
		if(_invulTime > 0) {
			if((_invulTime - elapsed_millis/1000.0)< 0) {
				_invulTime = 0;
				setCollisionRadius(_size[1]/2);
			} else {
				_invulTime-= elapsed_millis/1000.0;
				setCollisionRadius(_size[1]*1.1);
			}
		}		
	}
	
	void SpaceShip::drawOverlay() {
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		GLboolean lightingEnabled;
		lightingEnabled = glIsEnabled(GL_LIGHTING);
		if(lightingEnabled == GL_TRUE) glDisable(GL_LIGHTING);
		
		cg::Vector2d position = getPosition();
		cg::Vector2d windowSize = cg::Vector2d(win.width, win.height);
		cg::Vector2d relativePosition = position / windowSize;
		std::ostringstream health;
		

		health << "H: " << floor(getHealth(true)) << "%";
		std::ostringstream ammo;
		ammo << "A: " << _charlesBronsonStyle;
		glColor3d(0.4,0.7,0.9);
		cg::Util::instance()->drawBitmapString(health.str(),position[0]-18,position[1]-25);
		cg::Util::instance()->drawBitmapString(ammo.str(),position[0]-18,position[1]-35);
		if(_radarAdvanced == 1) {
			cg::Vector3d tip = cg::Vector3d(_size[0], 0, 0)/2.0;
			cg::Vector3d leftCorner = cg::Vector3d(-_size[0], -_size[1], 0)/2.0;
			cg::Vector3d rightCorner = cg::Vector3d(-_size[0], _size[1], 0)/2.0;
			glColor3d(1-getHealth(true)/100,getHealth(true)/100-0.1,0.2);		

			glPushMatrix();
			{
				glTranslated(win.width-win.width/_radarSize +  relativePosition[0]*win.width/_radarSize, relativePosition[1]*win.height/_radarSize, 0);
				glRotated(getRotation(true), 0, 0, 1);
				glScaled(1.5/_radarSize, 1.5/_radarSize, 1.5/_radarSize);
				glBegin(GL_TRIANGLES); 
				{
					glVertex3d(tip[0], tip[1], tip[2]);			
					glVertex3d(leftCorner[0], leftCorner[1], leftCorner[2]);			
					glVertex3d(rightCorner[0], rightCorner[1], rightCorner[2]);	
				}
				glEnd();
			}
			glPopMatrix();
		} else {
			cg::Util::instance()->drawStrokeString("S", win.width-win.width/_radarSize +  relativePosition[0]*win.width/_radarSize , relativePosition[1]*win.height/_radarSize,0.1,false,2,0.1,0.9,0.4,1);
		}
		

		if(lightingEnabled == GL_TRUE) glEnable(GL_LIGHTING);
	}

	void SpaceShip::draw() {
		cg::Vector3d tip = cg::Vector3d(_size[0], 0, 0)/2.0;
		cg::Vector3d backTip = cg::Vector3d(-_size[0], 0, 0) / 1.5;
		cg::Vector3d topLeftCorner = cg::Vector3d(-_size[0], -_size[1], _size[1])/2.0;
		cg::Vector3d topRightCorner = cg::Vector3d(-_size[0], _size[1], _size[1])/2.0;
		cg::Vector3d bottomLeftCorner = cg::Vector3d(-_size[0], -_size[1], -_size[1])/2.0;
		cg::Vector3d bottomRightCorner = cg::Vector3d(-_size[0], _size[1], -_size[1])/2.0;
		
		GLfloat positionLight[]={tip[0],tip[1],tip[2],0.8};
		GLfloat directionLight[]={1,0,0};
		cg::Vector2d position = getPosition();
		
		glPushMatrix();
		{
			glTranslated(position[0], position[1], 0);
			glRotated(getRotation(true), 0, 0, 1);
			glLightfv(GL_LIGHT1, GL_POSITION,positionLight);
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,directionLight);
			
			glColor3d(1-getHealth(true)/100,getHealth(true)/100-0.1,0.2);
			cg::Vector3d normal = cg::Vector3d(0,0,0);

			//top face
			glBegin(GL_POLYGON);
			{
				//glColor3d(1,0, 0);
				normal = normalize(tip);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(tip[0], tip[1], tip[2]);

				normal = normalize(topLeftCorner);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(topLeftCorner[0], topLeftCorner[1], topLeftCorner[2]);

				normal = normalize(topRightCorner);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(topRightCorner[0], topRightCorner[1], topRightCorner[2]);
			}
			glEnd();

			//bottom face
			glBegin(GL_POLYGON);
			{
				//glColor3d(0, 1, 0);
				normal = normalize(tip);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(tip[0], tip[1], tip[2]);

				normal = normalize(bottomLeftCorner);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(bottomLeftCorner[0], bottomLeftCorner[1], bottomLeftCorner[2]);

				normal = normalize(bottomRightCorner);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(bottomRightCorner[0], bottomRightCorner[1], bottomRightCorner[2]);
			}
			glEnd();

			//right face
			glBegin(GL_POLYGON);
			{
				//glColor3d(0 ,0, 1);
				normal = normalize(tip);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(tip[0], tip[1], tip[2]);

				normal = normalize(topRightCorner);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(topRightCorner[0], topRightCorner[1], topRightCorner[2]);

				normal = normalize(bottomRightCorner);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(bottomRightCorner[0], bottomRightCorner[1], bottomRightCorner[2]);
			}
			glEnd();
			
			//left face
			glBegin(GL_POLYGON);
			{
				//glColor3d(1,1, 0);
				normal = normalize(tip);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(tip[0], tip[1], tip[2]);

				normal = normalize(topLeftCorner);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(topLeftCorner[0], topLeftCorner[1], topLeftCorner[2]);

				normal = normalize(bottomLeftCorner);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(bottomLeftCorner[0], bottomLeftCorner[1], bottomLeftCorner[2]);
			}
			glEnd();

			//bottom
			glBegin(GL_QUADS);
			{
				//glColor3d(0,1, 1);
				normal = normalize(topLeftCorner);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(topLeftCorner[0], topLeftCorner[1], topLeftCorner[2]);

				normal = normalize(topRightCorner);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(topRightCorner[0], topRightCorner[1], topRightCorner[2]);

				normal = normalize(bottomLeftCorner);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(bottomLeftCorner[0], bottomLeftCorner[1], bottomLeftCorner[2]);

				normal = normalize(bottomRightCorner);
				glNormal3d(normal[0], normal[1], normal[2]);
				glVertex3d(bottomRightCorner[0], bottomRightCorner[1], bottomRightCorner[2]);
			}
			glEnd();
		}
		glPopMatrix();
		//glFlush();

		if(_invulTime > 0) {
			glPushMatrix();
			{
				GLboolean blendEnabled, depthTestEnabled;
				blendEnabled = glIsEnabled(GL_BLEND);
				depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
				if(blendEnabled != GL_TRUE) glEnable(GL_BLEND);
				if(depthTestEnabled == GL_TRUE) glDisable(GL_DEPTH_TEST);
				glBlendFunc(GL_SRC_ALPHA,GL_ONE);
				
				glTranslated(position[0], position[1], 0);
				glColor4d(0.17, 0.67, 1, _invulTime/_invulTimeMax*0.6);
				glutSolidSphere(_size[1]*1.1, 35, 35);
				
				if(depthTestEnabled == GL_TRUE) glEnable(GL_DEPTH_TEST);
				if(blendEnabled != GL_TRUE) glDisable(GL_BLEND);
			}
			glPopMatrix();		
		}

	}
	
	void SpaceShip::dealDamage(double damage) {
		if(_invulTime > 0)
			return;
		//else
		Particle::dealDamage(damage);
	}
	
	double SpaceShip::getCollisionDamage(Particle * target) {
		if(_invulTime > 0)
			return 0;
		//else
		return Particle::getCollisionDamage(target);	
	}
	
	
	void SpaceShip::onReshape(int width, int height) {
		if(width > 100 && height > 100) {
			setUniverseDimensions(width,height);
		}
	}

	void SpaceShip::hyperAccelerate(void) {
		_hyperAccelerator->hyperAccelerate();
	}
	
	void SpaceShip::shootLaser(void) {
		if (_charlesBronsonStyle > 0 && _invulTime == 0) {
			_charlesBronsonStyle--;
			getParticleManager()->createLaserShot(getPosition(), getRotation(), getVelocity(), getRotation(true));
		}
	}
	void SpaceShip::onKeyPressed(unsigned char key) {
		_controller->onKeyPressed(key);
	}
	
	void SpaceShip::onKeyReleased(unsigned char key) {
		_controller->onKeyReleased(key);
	}
	

	
}