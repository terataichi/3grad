#include <cassert>
#include "AnimationManager.h"
#include "ImageManager.h"

std::unique_ptr<AnimationManager, AnimationManager::AnimationManagerDeleter>AnimationManager::sInstance_(new AnimationManager);

AnimationManager::AnimationManager()
{
	stateMap_.try_emplace(Anim_State::Non,"non");
	stateMap_.try_emplace(Anim_State::Max, "max");
	stateMap_.try_emplace(Anim_State::Normal, "normal");
	stateMap_.try_emplace(Anim_State::Run, "run");
	stateMap_.try_emplace(Anim_State::Walk, "walk");
	stateMap_.try_emplace(Anim_State::Dmage, "damage");
	stateMap_.try_emplace(Anim_State::Death, "death");
}

AnimationManager::~AnimationManager()
{
}

const std::string AnimationManager::AddAnimation(const std::string& path,std::string key)
{
	// 登録されているかチェック
	// すでに登録されてたらキーを作成してあげる
	// contains : c++20から
	int count = 1;
	while (animMap_.contains(key))
	{
		key += std::to_string(count);
		count++;
	}
	// TMX読み込み
	std::unique_ptr<TmxAnimation> animation_;
	animation_ = std::make_unique<TmxAnimation>(path);

	// 登録する情報の格納
	Animation anim;
	anim.imageData_ = animation_->GetImageData();
	lpImageManager.GetImageHandle(anim.imageData_.imageName, anim.imageData_.imageDivSize, anim.imageData_.imageSize);

	anim.animVec_ = animation_->GetAnimData();
	anim.nowState_ = stateMap_[Anim_State::Non];
	anim.animCount_ = 0;
	anim.startTime_ = 0.0;

	// 登録
	animMap_.try_emplace(key, anim);

	return key;
}

int AnimationManager::GetAnimation(const std::string& key, const double& elapsedTime)
{
	// キーチェック
	if (animMap_.contains(key))
	{
		if (!animMap_[key].animVec_.contains(animMap_[key].nowState_))
		{
			assert(!"GetAnimation : ステータスが見つかりません");
		}
		const auto& state = animMap_[key].animVec_[animMap_[key].nowState_];
		double time = 0;
		while (state.loop == -1 ||  animMap_[key].animCount_ < state.loop)
		{
			for (const auto& vec : state.chipData)
			{
				// １コマの表示時間を加算して経過時間より大きくなったらそこが現在の表示コマになる
				time += vec.interval;
				if (time >= elapsedTime - animMap_[key].startTime_)
				{
					animMap_[key].animCount_ = 0;
					return 	lpImageManager.GetImageHandle(animMap_[key].imageData_.imageName,
						animMap_[key].imageData_.imageDivSize,
						animMap_[key].imageData_.imageSize)
						[vec.chip];
				}
			}
			if (state.loop == -1)
			{
				animMap_[key].startTime_ = elapsedTime;
			}
			animMap_[key].animCount_++;
		}
		return -1;
	}
	assert(!"GetAnimation : キーが見つかりません");
	return -1;
}

bool AnimationManager::SetState(const std::string& key, const Anim_State& state, const double& nowElapsedTime)
{
	if (animMap_.contains(key))
	{
		// 対応するステータスがあるか
		if (!animMap_[key].animVec_.contains(stateMap_[state]))
		{
			assert(!"SetState : ステータスが見つかりません");
			return false;
		}

		// いまと同じだったらリセットしない
		if (animMap_[key].nowState_ == stateMap_[state])
		{
			return true;
		}
		animMap_[key].nowState_ = stateMap_[state];
		animMap_[key].animCount_ = 0;
		animMap_[key].startTime_ = nowElapsedTime;
		return true;
	}
	assert(!"SetState : キーが見つかりません");
	return false;
}

const Sizef AnimationManager::GetChipSize(const std::string& key)
{
	if (animMap_.contains(key))
	{
		return Sizef(animMap_[key].imageData_.imageSize);
	}

	return Sizef::ZERO;
}
