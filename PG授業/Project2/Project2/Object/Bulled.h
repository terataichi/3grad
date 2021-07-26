#pragma once
#include "Object.h"
class Bulled :
    public Object
{
public:
	Bulled(Potision2f& pos, Vector2f& vel, TeamTag tag = TeamTag::Non);
	~Bulled();
	void Draw();
protected:
};

