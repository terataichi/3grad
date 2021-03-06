#pragma once
#include "TransitionScene.h"
class BlockDropScene :
    public TransitionScene
{
public:
	BlockDropScene(UniqueBase beforScene, UniqueBase afterScene, double&& limit);
	~BlockDropScene();

private:
	bool TransitionUpdate()override;
	void DrawOwnScreen()override;

	double limit_;													// 何秒で完了してほしいか
	double time_;													// 経過時間
	double fadeCount_;												// 画面効果用

	Size division_;
	int size_;
	float speed_;
	float count_;
};

