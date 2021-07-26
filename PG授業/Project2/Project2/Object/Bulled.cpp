#include "Bulled.h"
#include "../TimeManager.h"
#include "../common/ImageManager.h"
#include "../common/AnimationManager.h"
#include "Pawn.h"

#include<DxLib.h>

Bulled::Bulled(Potision2f& pos, Vector2f& vel, TeamTag tag) :Object(pos, vel,ObjectType::Actor,tag)
{
}

Bulled::~Bulled()
{
}

void Bulled::Draw()
{
	auto pos = static_cast<Potision2>(pos_);

	lpAnimManager.SetState(animKey_, animState_, lpTimeManager.GetElapsedTime());
	DrawRotaGraph(pos.x_, pos.y_, 1, 0.0, lpAnimManager.GetAnimation(animKey_, lpTimeManager.GetElapsedTime()), true, turn_);
}
