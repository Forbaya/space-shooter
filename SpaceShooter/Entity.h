#ifndef ENTITY_H
#define ENTITY_H

#include "AxisInput.h"

class Entity {
	public:
		virtual void Tick(AxisInput *axisInput)=0;
		virtual void Move(int x, int y)=0;
};

#endif