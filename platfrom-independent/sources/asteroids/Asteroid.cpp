/*
 Roids!
 Copyright (C) 2008 Carlos Lage, Tiago Coelho, Eduardo Castanho

 This file is part of Roids!.

 Roids! is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 Roids! is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Roids!; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "Asteroid.h"
#include "GameManager.h"
#include "Maths.h"

namespace asteroids
{

	Asteroid::Asteroid(std::string id, double scaleFactor, GameManager *gameManager) : GameEntity(id, gameManager, 'a'),
																					   _scaleFactor(scaleFactor), _skipColoring(false)
	{
	}

	Asteroid::Asteroid(std::string id, double scaleFactor, GameManager *gameManager, double red, double green, double blue) : GameEntity(id, gameManager, 'a'),
																															  _scaleFactor(scaleFactor), _red(red), _green(green), _blue(blue), _skipColoring(true)
	{
	}

	Asteroid::Asteroid(std::string id, GameManager *gameManager) : GameEntity(id, gameManager, 'a'),
																   _scaleFactor(randomBetween(2, 6)), _skipColoring(false)
	{
	}

	Asteroid::~Asteroid()
	{
	}

	void Asteroid::init()
	{
		// Read from property file
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		setUniverseDimensions(win.width, win.height);
		setVelocity(cg::Vector2d(randomBetween(-100, 100), randomBetween(-100, 100)));
		setCollisionCenter(getPosition());
		_baseAsteroidMass = cg::Properties::instance()->getDouble("ASTEROID_BASE_MASS");
		setMass(_baseAsteroidMass * _scaleFactor);
		setHealth(getMass());

		_radarSize = cg::Properties::instance()->getDouble("RADAR_SIZE");
		_radarAdvanced = cg::Properties::instance()->getInt("RADAR_ADVANCED");

		_invulSeconds = cg::Properties::instance()->getDouble("ASTEROID_INVUL_SECONDS");

		cg::Vector3d t;
		int i;
		double x, y, angle;

		_baseAsteroidSize = cg::Properties::instance()->getDouble("ASTEROID_BASE_SIZE");
		_radius = _baseAsteroidSize * _scaleFactor;
		setCollisionRadius(_radius * 0.75);
		startRotation(randomBetween(-length(getVelocity()), length(getVelocity())));

		if (!_skipColoring)
		{
			_red = randomBetween(0.2, 0.8);
			_green = randomBetween(0.2, 0.8);
			_blue = randomBetween(0.2, 0.8);
		}

		for (i = 0; i < 12; i++)
		{
			angle = 2 * (3.14) * i / 12;
			x = cos(angle) * randomBetween(0.5, 0.9) * _baseAsteroidSize * _scaleFactor;
			y = sin(angle) * randomBetween(0.5, 0.9) * _baseAsteroidSize * _scaleFactor;
			t = cg::Vector3d(x, y, 0);
			_asteroid_vector.push_back(t);
			x = cos(angle) * randomBetween(0.5, 0.9) * (_baseAsteroidSize * 0.7) * _scaleFactor;
			y = sin(angle) * randomBetween(0.5, 0.9) * (_baseAsteroidSize * 0.7) * _scaleFactor;
			t = cg::Vector3d(x, y, (_radius / 2));
			_asteroid_vector2.push_back(t);
		}
	}

	void Asteroid::update(unsigned long elapsed_millis)
	{
		if (isDestroyed() == true)
			return;
		if (_invulSeconds > 0)
		{
			if ((_invulSeconds - elapsed_millis / 1000.0) < 0)
			{
				_invulSeconds = 0;
			}
			else
			{
				_invulSeconds -= elapsed_millis / 1000.0;
			}
		}
		PhysicsObject::update(elapsed_millis);
		checkCollisions(elapsed_millis);

		setRotationFactor(length(getVelocity()) * getRotationFactor() / getRotationFactor());
	}

	void Asteroid::draw()
	{
		if (isDestroyed() == true)
			return;

		cg::Vector3d t;
		cg::Vector2d position = getPosition();

		glPushMatrix();
		{
			glTranslated(position[0], position[1], 0);
			glRotated(getRotation(true), 1, 1, 1);
			//glEnable(GL_NORMALIZE);
			std::vector<cg::Vector3d>::iterator q = _asteroid_vector2.begin();
			std::vector<cg::Vector3d>::iterator pBegin = _asteroid_vector.begin();
			std::vector<cg::Vector3d>::iterator qBegin = _asteroid_vector2.begin();

			glColor3d(_red, _green, _blue);
			GLfloat materialSpecReflection[] = {(float)_red, (float)_green, (float)_blue, 1.0f};

			GLfloat materialEmission[] = {0.0f, 0.0f, 0.0f, 1.0f};
			glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecReflection);
			glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
			glMateriali(GL_FRONT, GL_SHININESS, 60);

			glBegin(GL_QUAD_STRIP);
			{
				cg::Vector3d normal = cg::Vector3d(0, 0, 0);

				for (std::vector<cg::Vector3d>::iterator p = _asteroid_vector.begin(); p != _asteroid_vector.end(); p++)
				{
					normal = normalize(cg::Vector3d((*p)[0], (*p)[1], (*p)[2]));
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f((*p)[0], (*p)[1], (*p)[2]);
					//glColor3d(0.4,0.4,0.4);
					normal = normalize(cg::Vector3d((*q)[0], (*q)[1], (*q)[2]));
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f((*q)[0], (*q)[1], (*q)[2]);
					//glColor3d(0.47,0.47,0.47);
					q++;
				}
				normal = normalize(cg::Vector3d((*pBegin)[0], (*pBegin)[1], (*pBegin)[2]));
				glNormal3f(normal[0], normal[1], normal[2]);
				glVertex3f((*pBegin)[0], (*pBegin)[1], (*pBegin)[2]);
				//glColor3d(0.4,0.4,0.4);
				normal = normalize(cg::Vector3d((*qBegin)[0], (*qBegin)[1], (*qBegin)[2]));
				glNormal3f(normal[0], normal[1], normal[2]);
				glVertex3f((*qBegin)[0], (*qBegin)[1], (*qBegin)[2]);
			}
			glEnd();

			glBegin(GL_TRIANGLE_STRIP);
			{
				cg::Vector3d normal = cg::Vector3d(0, 0, 0);
				for (std::vector<cg::Vector3d>::iterator q = _asteroid_vector2.begin(); q != _asteroid_vector2.end(); q++)
				{
					//glColor3d(0.4,0.4,0.4);
					normal = normalize(cg::Vector3d((*q)[0], (*q)[1], (*q)[2]));
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f((*q)[0], (*q)[1], (*q)[2]);
					//glColor3d(0.47,0.47,0.47);
					normal = normalize(cg::Vector3d(_scaleFactor * 2, _scaleFactor * 3, _radius * 0.7));
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f(_scaleFactor * 2, _scaleFactor * 3, _radius * 0.7);
				}
				normal = normalize(cg::Vector3d((*qBegin)[0], (*qBegin)[1], (*qBegin)[2]));
				glNormal3f(normal[0], normal[1], normal[2]);
				glVertex3f((*qBegin)[0], (*qBegin)[1], (*qBegin)[2]);
			}
			glEnd();

			//bottom
			glBegin(GL_QUAD_STRIP);
			{
				q = _asteroid_vector2.begin();
				cg::Vector3d normal = cg::Vector3d(0, 0, 0);
				//glColor3d(0.47,0.47,0.47);
				for (std::vector<cg::Vector3d>::iterator p = _asteroid_vector.begin(); p != _asteroid_vector.end(); p++)
				{
					normal = normalize(cg::Vector3d((*p)[0], (*p)[1], -(*p)[2]));
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f((*p)[0], (*p)[1], -(*p)[2]);
					//glColor3d(0.4,0.4,0.4);
					normal = normalize(cg::Vector3d((*q)[0], (*q)[1], -(*q)[2]));
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f((*q)[0], (*q)[1], -(*q)[2]);
					//glColor3d(0.47,0.47,0.47);
					q++;
				}
				normal = normalize(cg::Vector3d((*pBegin)[0], (*pBegin)[1], -(*pBegin)[2]));
				glNormal3f(normal[0], normal[1], normal[2]);
				glVertex3f((*pBegin)[0], (*pBegin)[1], -(*pBegin)[2]);
				//glColor3d(0.4,0.4,0.4);
				normal = normalize(cg::Vector3d((*qBegin)[0], (*qBegin)[1], -(*qBegin)[2]));
				glNormal3f(normal[0], normal[1], normal[2]);
				glVertex3f((*qBegin)[0], (*qBegin)[1], -(*qBegin)[2]);
			}
			glEnd();

			glBegin(GL_TRIANGLE_STRIP);
			{
				cg::Vector3d normal = cg::Vector3d(0, 0, 0);
				for (std::vector<cg::Vector3d>::iterator q = _asteroid_vector2.begin(); q != _asteroid_vector2.end(); q++)
				{
					//glColor3d(0.4,0.4,0.4);
					normal = normalize(cg::Vector3d((*q)[0], (*q)[1], -(*q)[2]));
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f((*q)[0], (*q)[1], -(*q)[2]);
					//glColor3d(0.47,0.47,0.47);
					normal = normalize(cg::Vector3d(_scaleFactor * 2, _scaleFactor * 3, -_radius * 0.7));
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f(_scaleFactor * 2, _scaleFactor * 3, -_radius * 0.7);
				}
				normal = normalize(cg::Vector3d((*qBegin)[0], -(*qBegin)[1], -(*qBegin)[2]));
				glNormal3f(normal[0], normal[1], normal[2]);
				glVertex3f((*qBegin)[0], -(*qBegin)[1], -(*qBegin)[2]);
			}
			glEnd();
		}
		glPopMatrix();
		//glFlush();

		/*
        glPushMatrix();
		{
			glTranslated(position[0], position[1], 0);
			//glRotated(getRotation(true), 0, 0, 1);
			glColor3d(1, 0, 0);
			glutSolidSphere(getCollisionRadius(), 30, 30);
			//glColor3d(0, 1, 0);
			//glutWireSphere(getCollisionRadius()-5, 30, 30);
			glColor3d(0, 0, 1);
			glutWireSphere(getCollisionRadius()-5, 30, 30);
		}
		glPopMatrix();
		glFlush();
        */
	}

	bool Asteroid::collidesWith(PhysicsObject *pobject)
	{
		if (isDestroyed() == true || _invulSeconds > 0)
			return false;
		//else
		return PhysicsObject::collidesWith(pobject);
	}

	void Asteroid::checkCollisions(double long elapsed_millis)
	{
		if (_invulSeconds > 0)
			return;

		Particle::checkCollisions(elapsed_millis);
	}

	void Asteroid::destroy(void)
	{

		if (_scaleFactor >= 2)
		{
			int newAsteroids = randomBetween(abs(int(_scaleFactor / 2 + 0.5)), abs(int(_scaleFactor * 1.1 + 0.5)));
			//int newAsteroids = abs(int(_scaleFactor + 0.5));
			double newScaleFactor = 0, newScaleDelta = 0;

			if (newAsteroids > _scaleFactor)
			{
				newAsteroids = abs(int(_scaleFactor + 0.5));
				newScaleFactor = 1;
				newScaleDelta = 1;
			}
			else if (newAsteroids > 1)
			{
				newScaleFactor = _scaleFactor / (double)newAsteroids;
				newScaleDelta = newScaleFactor / _scaleFactor;
			}
			else if (newAsteroids == 1)
			{
				newScaleFactor = 0.5 * _scaleFactor;
				newAsteroids = 2;
				newScaleDelta = 0.4;
			}
			getGameManager()->createAsteroids(newAsteroids, newScaleFactor, getCollisionRadius(), getPosition(), newScaleDelta, _red, _green, _blue);
		}
		Particle::destroy();
	}

	void Asteroid::drawOverlay()
	{
		if (isDestroyed() == true)
			return;

		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);

		cg::Vector2d position = getPosition();
		cg::Vector2d windowSize = cg::Vector2d(win.width, win.height);
		cg::Vector2d relativePosition = position / windowSize;

		if (_radarAdvanced == 1)
		{
			cg::Vector3d tip = cg::Vector3d(_size[0], 0, 0) / 2.0;
			cg::Vector3d leftCorner = cg::Vector3d(-_size[0], -_size[1], 0) / 2.0;
			cg::Vector3d rightCorner = cg::Vector3d(-_size[0], _size[1], 0) / 2.0;
			glPushMatrix();
			{
				glTranslated(win.width - win.width / _radarSize + relativePosition[0] * win.width / _radarSize, relativePosition[1] * win.height / _radarSize, 0);
				glRotated(getRotation(true), 0, 0, 1);
				glScaled(1 / _radarSize, 1 / _radarSize, 1 / _radarSize);
				glColor3d(0.4, 0.7, 0.9);
				glBegin(GL_LINE_LOOP);
				{
					for (std::vector<cg::Vector3d>::iterator p = _asteroid_vector.begin(); p != _asteroid_vector.end(); ++p)
					{
						glVertex3f((*p)[0], (*p)[1], (*p)[2]);
					}
				}
				glEnd();
			}
			glPopMatrix();
		}
		else
		{
			cg::Util::instance()->drawStrokeString("@", win.width - win.width / _radarSize + relativePosition[0] * win.width / _radarSize, relativePosition[1] * win.height / _radarSize, 0.0075 * _scaleFactor * _baseAsteroidSize, false, 2, 0.4, 0.7, 0.9, 1);
		}

		glPopAttrib();
	}
} // namespace asteroids
