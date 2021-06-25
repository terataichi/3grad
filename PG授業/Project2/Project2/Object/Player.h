#pragma once
#include <memory>

#include "Object.h"

class Controller;
class TmxAnimation;
class TileMap;

class Player:
	public Object
{
public:
	Player(Potision2f&& pos, Vector2f&& speed, std::shared_ptr<TileMap>& tileMap,ControllType type = ControllType::Keybord);
	~Player();

	void Init(ControllType type)override;
	bool Update(const double& delta) override;
	void Draw(const double& delta) override;
private:
	Sizef GetOffSet(Vector2f vel);

	std::shared_ptr<TileMap> tileMap_;						// ゲームシーンからもらってくる
};

