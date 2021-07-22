#pragma once
#include "Object.h"
class Bulled :
    public Object
{
public:
	Bulled(Potision2f&& pos, Vector2f&& vel, TeamTag tag = TeamTag::Non);
	~Bulled();

	void Init();
	bool Update();
	void Draw();
	void Hit(std::shared_ptr<Object> target);
protected:
	std::string name_;
};

