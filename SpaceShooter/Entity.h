#ifndef ENTITY_H
#define ENTITY_H

class Entity {
	public:
		virtual void Tick()=0;
		virtual void Move(int x, int y)=0;
};

#endif