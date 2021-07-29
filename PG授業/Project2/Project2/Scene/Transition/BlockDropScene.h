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

	double limit_;													// ‰½•b‚ÅŠ®—¹‚µ‚Ä‚Ù‚µ‚¢‚©
	double time_;													// Œo‰ßŽžŠÔ
	double fadeCount_;												// ‰æ–ÊŒø‰Ê—p

	Size division_;
	int size_;
	float speed_;
	float count_;
};

