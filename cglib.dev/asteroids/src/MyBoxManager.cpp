#include "MyBoxManager.h"

namespace asteroids {

	MyBoxManager::MyBoxManager(std::string id) : cg::Group(id) {
	}
	MyBoxManager::~MyBoxManager() {
	}
	void MyBoxManager::createEntities() {
		int nbox = cg::Properties::instance()->getInt("NBOX");
		for(int i = 0; i < nbox; i++) {
			std::ostringstream os;
			os << "Box" << i;
			add(new MyBox(os.str()));
		}
	}
	void MyBoxManager::postInit() {
        std::ostringstream os;
        os << size() << " boxes on screen.";
		_nboxMessage = os.str();
	}
	void MyBoxManager::drawOverlay() {
		glColor3d(0.9,0.1,0.1);
		cg::Util::instance()->drawBitmapString(_nboxMessage,10,10);
	}
}