#pragma once
#include "Bulled.h"

class FireBulled :
    public Bulled
{
public:
	FireBulled(Potision2f&& pos, Vector2f&& vel,int&& damage, TeamTag tag = TeamTag::Non);

	void Init() override;
	bool Update() override;
	void Hit(std::shared_ptr<Object> target) override;

private:
	int damage_;
};

