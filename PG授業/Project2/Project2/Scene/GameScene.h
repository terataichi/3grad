#pragma once
#include "BaseScene.h"
#include <memory>
#include <vector>
#include <list>

class TileMap;
class Object;
class Pawn;
class Collision;

class GameScene :
    public BaseScene
{
public:
    GameScene();
    ~GameScene();

private:
    bool Init(void)override;
    UniqueBase Update(UniqueBase scene)override;
    void DrawOwnScreen()override;
    SceneName MyName()override { return SceneName::Game; };

    bool AddInstanceList(std::shared_ptr<Pawn>& pawn);

    std::list<std::shared_ptr<Object>> instanceList_;
    std::list<std::shared_ptr<Object>> objList_;
    std::shared_ptr<TileMap> map_;
    std::unique_ptr<Collision> collision_;

    int deathScreen_;
};

