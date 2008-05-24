#pragma once
#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H
#pragma message("ScreenManager is included")

#include <sstream>
#include <string>
#include <vector>
#include "cg/cg.h"
#include "Screen.h"

namespace asteroids {

	class ScreenManager : public cg::Group,
		public cg::GroupReshapeEvent,
		public cg::GroupDrawOverlay
	{
	protected:
		void createEntities();
	public:
		ScreenManager();
		~ScreenManager();
		void addScreen(Screen * s);
		void removeScreen(Screen * s);
	};
}

#endif