//BEGIN: MEMORY LEAK DETECTION
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//END: MEMORY LEAK DETECTION

#include <ctime>
#include "cg/cg.h"
#include "MyApp.h"

int main(int argc, char** argv) {

//BEGIN: MEMORY LEAK DETECTION
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc(xxx);
//END: MEMORY LEAK DETECTION

	srand(time(0));
	cg::Manager::instance()->runApp(new asteroids::MyApp(),60,argc,argv);
	return 0;
}