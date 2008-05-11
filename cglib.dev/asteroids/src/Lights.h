#ifndef LIGHTS_H
#define LIGHTS_H

#include "cg/cg.h"

namespace asteroids {

    class Lights : public cg::Entity
	{
    public:
        Lights();
        virtual ~Lights();
        void init();
  
	};
}

#endif