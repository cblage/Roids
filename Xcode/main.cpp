#include <stdlib.h>
#include <ctime>
#include "cg/cg.h"
#include "MyApp.h"

int main(int argc, char** argv) {
	srand(time(0));
	cg::Manager::instance()->runApp(new asteroids::MyApp(),60,argc,argv);
	return 0;
}