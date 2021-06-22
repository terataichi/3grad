#include <cassert>
#include "AnimationManager.h"
#include "ImageManager.h"

std::unique_ptr<AnimationManager, AnimationManager::AnimationManagerDeleter>AnimationManager::sInstance_(new AnimationManager);

AnimationManager::AnimationManager()
{
	stateMap_.try_emplace(Animation_State::Non,"non");
	stateMap_.try_emplace(Animation_State::Max, "max");
	stateMap_.try_emplace(Animation_State::Normal, "normal");
	stateMap_.try_emplace(Animation_State::Run, "run");
	stateMap_.try_emplace(Animation_State::Walk, "walk");
}

AnimationManager::~AnimationManager()
{
}

bool AnimationManager::AddAnimation(const std::string key, const AnimDataMap& animData, const AnimImageData& animImageData)
{
	// 登録されているかチェック
	// contains : c++20から
	if (!animMap_.contains(key))
	{

		auto debug = lpImageManager.GetImageHandle(animImageData.imageName, animImageData.imageDivSize, animImageData.imageSize);

		Animation anim;
		anim.imageData = animImageData;
		anim.animVec = animData;
		//anim.nowState_ = stateMap_[Animation_State::Normal];

		// 登録
		animMap_.try_emplace(key, anim);
		return true;
	}

	// すでに登録されてたらキーを作成してあたらしく作ってあげてもいいかも

	//assert(!"AddAnimation : すでに登録されています");
	return false;
}

int AnimationManager::GetAnimation(const std::string key, double elapsedTime)
{
	// キーチェック
	if (animMap_.contains(key))
	{
		if (!animMap_[key].animVec.contains(animMap_[key].nowState_))
		{
			assert(!"GetAnimation : ステータスが見つかりません");
		}
		const auto& state = animMap_[key].animVec[animMap_[key].nowState_];
		while (state.loop == -1 || state.loop - animMap_[key].animCount_ > 0)
		{
			for (const auto& vec : state.chipData)
			{
				// １コマの表示時間を加算して経過時間より大きくなったらそこが現在の表示コマになる
				animMap_[key].time_ += vec.interval;
				if (animMap_[key].time_ >= elapsedTime)
				{
					animMap_[key].time_ = 0.0;

					return 	lpImageManager.GetImageHandle(animMap_[key].imageData.imageName,
						animMap_[key].imageData.imageDivSize,
						animMap_[key].imageData.imageSize)
						[vec.chip];
				}
			}
			animMap_[key].animCount_++;
		}
		return -1;
	}
	assert(!"GetAnimation : キーが見つかりません");
	return -1;
}

bool AnimationManager::SetState(const std::string& key, const Animation_State& state)
{
	if (animMap_.contains(key))
	{
		// 対応するステータスがあるか
		if (!animMap_[key].animVec.contains(stateMap_[state]))
		{
			assert(!"SetState : ステータスが見つかりません");
			return false;
		}
		animMap_[key].nowState_ = stateMap_[state];
		animMap_[key].time_ = 0.0f;
		animMap_[key].animCount_ = 0;
		return true;
	}
	assert(!"SetState : キーが見つかりません");
	return false;
}
