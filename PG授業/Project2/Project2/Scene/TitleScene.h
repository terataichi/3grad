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
    UniqueBase Update(UniqueBase scene)override;
    void DrawOwnScreen()override;
    SceneName MyName()override { return SceneName::Title; };
};

