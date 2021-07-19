#pragma once
#include "Object.h"
class Bulled :
    public Object
{
public:
	Bulled(Potision2f&& pos, Vector2f&& vel);
	~Bulled();

	virtual void Init();
	virtual bool Update();
	virtual void Draw();

protected:
	std::string name_;

};

