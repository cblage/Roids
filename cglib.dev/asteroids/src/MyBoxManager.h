#ifndef MY_BOX_MANAGER_H
#define MY_BOX_MANAGER_H

#include <sstream>
#include <string>
#include <vector>
#include "cg/cg.h"
#include "MyBox.h"

namespace asteroids {

	class MyBoxManager : public cg::Group,
		public cg::GroupDraw,
		public cg::GroupUpdate,
		public cg::GroupReshapeEvent,
		public cg::IDrawOverlayListener
	{
	private:
		std::string _nboxMessage;
	protected:
		void createEntities();
		void postInit();
	public:
		MyBoxManager(std::string id);
		~MyBoxManager();
		void drawOverlay();
	};
}

#endif