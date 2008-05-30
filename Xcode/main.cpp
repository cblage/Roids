#include <stdlib.h>
#include <TargetConditionals.h>
#include <ctime>
#include "cg/cg.h"
#include "MyApp.h"

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
	cg::Manager::instance()->runApp(new asteroids::MyApp(), 60,argc,argv);
	return 0;
}