#pragma once
#include <memory>
#include <string>
#include "BaseScene.h"
#include "../common/Vector2.h"

class TileMap;
class Object;

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

    std::unique_ptr<Object> object_;
    std::shared_ptr<TileMap> map_;
};

