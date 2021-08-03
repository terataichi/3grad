#pragma once
#include "Object.h"
class StartObj :
    public Object
{
public:
	StartObj(Potision2f&& pos, Vector2f&& vel, Size&& size, TeamTag tag = TeamTag::Non);
	~StartObj();

	void Init() override;
	bool Update() override;
	void Hit(std::shared_ptr<Object> target) override;
	void Draw();
};

