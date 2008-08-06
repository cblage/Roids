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
#include "Lights.h"

namespace asteroids {

    Lights::Lights() : Entity("Lights") {
	}
    Lights::~Lights() {
	}
    void Lights::init() {
		GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
		GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
		GLfloat specularLight[] = { 0.5, 0.5, 0.5, 1.0 };

		GLfloat diffuseLight1[] = { 1, 1, 1, 1.0 };
		GLfloat specularLight1[] = { 1, 1, 1, 1.0 };
		GLfloat spotAngle=30;

		glEnable(GL_LIGHTING);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);

		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF,spotAngle);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);
		
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glShadeModel(GL_SMOOTH);

	}
}