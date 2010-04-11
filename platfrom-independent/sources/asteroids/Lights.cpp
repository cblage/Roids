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
		GLfloat ambientLight[] = { .0f, .0f, .0f, 1.0f };
		GLfloat diffuseLight[] = { 1.0f, .8f, .4f, 0.6f };
		GLfloat specularReflection[] = { 1.0f, .8f, .4f, 0.8f };
		GLfloat lightpos[] = { -100.5f, 100.0f, -40.0f, .0f };
	
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularReflection);
		glLightfv(GL_LIGHT0, GL_POSITION, lightpos);		

		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		glShadeModel(GL_SMOOTH);
	}
}

