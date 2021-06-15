#include "BrightRotationScene.h"

BrightRotationScene::BrightRotationScene(UniqueBase beforScene, UniqueBase afterScene, double&& limit)
	:TransitionScene(std::move(beforScene), std::move(afterScene))
{
	limit_ = limit;
	time_ = 0;
	fadeCount_ = 0;
}

BrightRotationScene::~BrightRotationScene()
{
}

bool BrightRotationScene::TransitionUpdate(const double& deltaTime)
{
	return false;
}

void BrightRotationScene::Draw(const double& deltaTime)
{
}
