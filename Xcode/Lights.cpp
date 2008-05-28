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