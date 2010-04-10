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
#include <stdlib.h>
#include <ctime>
#include <cg/cg.h>
#include "RoidsApp.h"

#if defined ( __APPLE__ )
	#include <TargetConditionals.h>
#endif
#if TARGET_OS_MAC
	#include <CoreFoundation/CoreFoundation.h>
#endif


int main(int argc, char** argv) {
#if TARGET_OS_MAC
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
	char path[PATH_MAX];
	if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))	{
		// error!
	}
	CFRelease(resourcesURL);
	chdir(path);
#endif
	srand(time(0));
	cg::Manager::instance()->runApp(new asteroids::RoidsApp(), 60,argc,argv);
	return 0;
}

