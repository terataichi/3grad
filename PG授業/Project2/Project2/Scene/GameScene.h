#pragma once
#include "BaseScene.h"
#include <memory>
#include <vector>
#include <list>

class TileMap;
class Object;

class GameScene :
    public BaseScene
{
public:
    GameScene();
    ~GameScene();

private:
    bool Init(void)override;
    UniqueBase Update(UniqueBase scene, const double& deltaTime)override;
    void DrawOwnScreen(const double& deltaTime)override;
    SceneName MyName()override { return SceneName::Game; };

    std::list<std::unique_ptr<Object>> objList_;
    std::unique_ptr<TileMap> map_;
};

