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
#include "SpaceShipHyperAccelerator.h"
#include "SpaceShip.h"
#include "Maths.h"

namespace asteroids
{

	SpaceShipHyperAccelerator::SpaceShipHyperAccelerator(SpaceShip *ship) : SpaceShipEngine(ship)
	{
		_hyperAccelerating = false;
	}
	SpaceShipHyperAccelerator::~SpaceShipHyperAccelerator(void)
	{
	}
	void SpaceShipHyperAccelerator::update(double elapsed_seconds)
	{
		if (_hyperAccelerating == false)
			return;

		cg::Vector2d universeDimensions = _ship->getUniverseDimensions();
		_ship->setPosition(cg::Vector2d(randomBetween(0, universeDimensions[0]), randomBetween(0, universeDimensions[1])));
		_hyperAccelerating = false;
	}
	void SpaceShipHyperAccelerator::hyperAccelerate(void)
	{
		_hyperAccelerating = true;
	}
} // namespace asteroids
