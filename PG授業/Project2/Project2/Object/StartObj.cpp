#include "StartObj.h"
#include <DxLib.h>

#include "Pawn.h"

StartObj::StartObj(Potision2f&& pos, Vector2f&& vel, Size&& size, TeamTag tag) :Object(pos, vel, ObjectType::Actor, tag)
{
	size_ = size;
}

StartObj::~StartObj()
{
}

void StartObj::Init()
{
}

bool StartObj::Update()
{
	return false;
}

void StartObj::Hit(std::shared_ptr<Object> target)
{
	target->SetActive(false);
}

void StartObj::Draw()
{
}
