#pragma once
#include <memory>
#include "BaseScene.h"

class TileMap;

class TitleScene :
    public BaseScene
{
public:
    TitleScene();
    ~TitleScene();

private:
    bool Init(void)override;
    UniqueBase Update(UniqueBase scene, const double& deltaTime)override;
    void DrawOwnScreen(const double& deltaTime)override;
    SceneName MyName()override { return SceneName::Title; };
};

