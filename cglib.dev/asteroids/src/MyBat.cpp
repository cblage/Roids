#include "MyBat.h"

namespace asteroids {

	MyBat::MyBat(std::string id) : cg::Entity(id) {
	}
	MyBat::~MyBat() {
	}
	void MyBat::init() {
		_size = cg::Properties::instance()->getVector2d("BAT_SIZE");
		_winHeight = cg::Manager::instance()->getApp()->getWindow().height;
	}
	void MyBat::draw() {
		cg::Vector2d min = _position - _size/2.0;
		cg::Vector2d max = _position + _size/2.0;
		glColor3d(0.9,0.9,0.9);
		glLineWidth(1.5);
		glBegin(GL_LINE_LOOP);
			glVertex3d(min[0],min[1], 0);
			glVertex3d(max[0],min[1], 0);
			glVertex3d(max[0],max[1], 0);
			glVertex3d(min[0],max[1], 0);
		glEnd();
	}
	void MyBat::onMouse(int button, int state, int x, int y) {
	}
	void MyBat::onMouseMotion(int x, int y) {
	}
	void MyBat::onMousePassiveMotion(int x, int y) {
		_position[0] = x;
		_position[1] = _winHeight - y;
	}
	bool MyBat::isCollision(cg::Vector2d box_position, cg::Vector2d box_size) {
		cg::Vector2d bat_bottomleft = _position - _size / 2.0;
		cg::Vector2d bat_topright = _position + _size / 2.0;
		cg::Vector2d box_bottomleft = box_position - box_size / 2.0;
		cg::Vector2d box_topright = box_position + box_size / 2.0;
		return cg::Util::instance()->isAABBoxCollision(bat_bottomleft,bat_topright,box_bottomleft,box_topright);
	}
	void MyBat::onReshape(int width, int height) {
		_winHeight = height;
	}
}