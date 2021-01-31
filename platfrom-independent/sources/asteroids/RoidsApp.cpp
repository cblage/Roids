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
#include "RoidsApp.h"
#include "Camera.h"
#include "StarSphere.h"
#include "GameManager.h"
#include "Lights.h"
#include "ApplicationState.h"
#include "BeforeGameState.h"
#include "BeforeLevelState.h"
#include "ApplicationController.h"
#include "ScreenManager.h"
#include "ExplosionManager.h"

namespace asteroids
{

	RoidsApp::RoidsApp() : cg::Application("config.ini")
	{
		_window.caption = "Roids! (Alpha Version)";
		_initialWindowWidth = cg::Properties::instance()->getInt("WINDOW_WIDTH");
		_initialWindowHeight = cg::Properties::instance()->getInt("WINDOW_HEIGHT");
		_forceInitialWindowSize = cg::Properties::instance()->getBool("WINDOW_FORCE_INITIAL_SIZE");
		_window.width = _initialWindowWidth;
		_window.height = _initialWindowHeight;
		_state = NULL;
		_gameManager = NULL;
		_screenManager = NULL;
		_explosionManager = NULL;
	}
	RoidsApp::~RoidsApp()
	{
	}
	void RoidsApp::createEntities()
	{
		_screenManager = new ScreenManager();
		_gameManager = new GameManager("GameManager", this);
		_explosionManager = new ExplosionManager("ExplosionManager", this);
		BeforeGameState::instance()->changeTo(this);
		addEntity(new ApplicationController(this));
		addEntity(new Camera());
		addEntity(new StarSphere());
		addEntity(_explosionManager);
		addEntity(_gameManager);
		addEntity(new Lights());
		addEntity(_screenManager);
	}

	void RoidsApp::changeState(ApplicationState *state)
	{
		if (state != _state)
		{
			_state = state;
		}
	}

	ApplicationState *RoidsApp::getState()
	{
		return _state;
	}

	void RoidsApp::onUpdate()
	{
		_state->onUpdate();
		_state->update(_time.elapsed);
	}

	void RoidsApp::onDisplay()
	{
		_state->onDisplay();
	}

	void RoidsApp::onKeyPressed(unsigned char key)
	{
		_state->onKeyPressed(key);
	}
	void RoidsApp::pause()
	{
		_state->pause();
	}
	void RoidsApp::quit()
	{
		_state->quit();
	}
	void RoidsApp::addScreen(Screen *s)
	{
		_screenManager->addScreen(s);
	}

	void RoidsApp::removeScreen(Screen *s)
	{
		_screenManager->removeScreen(s);
	}

	GameManager *RoidsApp::getGameManager()
	{
		return _gameManager;
	}

	ExplosionManager *RoidsApp::getExplosionManager()
	{
		return _explosionManager;
	}

	void RoidsApp::onReshape(int w, int h)
	{
		if (_forceInitialWindowSize)
		{
			glutReshapeWindow(_initialWindowWidth, _initialWindowHeight);
		}
		else
		{
			cg::Application::onReshape(w, h);
		}
	}

	void RoidsApp::resetTime()
	{
		updateFrameTime();
		_state->update(_time.elapsed);
	}
} // namespace asteroids
