// This file is part of CGLib.
//
// CGLib is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// CGLib is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CGLib; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
// Copyright 2007 Carlos Martinho

#ifndef DRAW_OVERLAY_NOTIFIER_H
#define DRAW_OVERLAY_NOTIFIER_H

#include "IDrawOverlayListener.h"
#include "Notifier.h"
#include "Singleton.h"

namespace cg {

	/** cg::DrawOverlayNotifier controls the drawOverlay step of the 
	 *  application, by calling the cg::IDrawOverlayListener::drawOverlay 
	 *  method of all the previously registered and currently enabled 
	 *  cg::IDrawOverlayListener's.
	 */

	class DrawOverlayNotifier : public Notifier<IDrawOverlayListener> {

	SINGLETON_HEADER(DrawOverlayNotifier)
	public:
		void drawOverlay();
		DUMP_METHOD(DrawOverlayNotifier)
	};
}

#endif // DRAW_OVERLAY_NOTIFIER_H