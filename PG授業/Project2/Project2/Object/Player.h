#pragma once
#include <memory>
#include <list>

#include "Pawn.h"
#include "../common/Raycast.h"

class Controller;
class TmxAnimation;
class TileMap;

class Player:
	public Pawn
{
public:
	Player(Potision2f&& pos, Vector2f&& speed, std::shared_ptr<TileMap>& tileMap,ControllType type = ControllType::Keybord);
	~Player();

	void Init()override;
	bool Update(const double& delta) override;
	void Draw(const double& delta) override;
private:
	Sizef GetOffSet(Vector2f vel);
	Raycast raycast_;
	std::shared_ptr<TileMap> tileMap_;							// �Q�[���V�[�����������Ă���
	std::map<InputID, std::list<Sizef>> offset_;				// ���C���΂����߂̂��

	float displacement_;										// �ω���
	double g_elapsedTime_;										// �d�͂̌o�ߎ��Ԍv���p
	bool jump_;													// �W�����v���邽�߂̃g���K�[
};

