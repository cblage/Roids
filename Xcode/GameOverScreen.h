#pragma once
#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H
#pragma message("GameOverScreen is included")

#include "Screen.h"


namespace asteroids {
	
	class GameOverScreen : public Screen
	{
	private:
		double _finalScore;
		unsigned int _finalLevel;
	public:
		GameOverScreen(std::string id, double finalScore, unsigned int finalLevel);
		~GameOverScreen();
		void drawOverlay();
	};
}

#endif