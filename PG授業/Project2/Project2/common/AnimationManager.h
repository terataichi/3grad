#pragma once
#include <memory>
#include <map>
#include <string>

#include "TmxAnimation.h"

#define lpAnimManager AnimationManager::GetInstance()

enum class Animation_State
{
	Non,
	Normal,
	Walk,
	Run,
	Max,
};

struct Animation
{
	AnimImageData imageData_;
	AnimDataMap animVec_;
	std::string oldState_;				// �O��̃X�e�[�^�X
	std::string nowState_;				// ���݂̃X�e�[�g
	int animCount_;						// ����Đ����ꂽ��
	double nowElapsedTime_;				// �X�e�[�^�X���ς�����Ƃ��Ɍo�ߎ��Ԃ�ۑ����Ă���
};

class AnimationManager
{
public:
	/// <summary>
	/// ���̂̎擾
	/// </summary>
	/// <returns>���̂��Ԃ�</returns>
	static AnimationManager& GetInstance()
	{
		return *sInstance_;
	}

	/// <summary>
	/// �A�j���[�V�����o�^
	/// �o�^����A�j���[�V�������ƃA�j���[�V�����̏��
	/// </summary>
	const std::string AddAnimation(const std::string& path,std::string key);
	/// <summary>
	/// �A�j���[�V�����̃R�}�擾
	/// </summary>
	/// <param name="key">�A�j���[�V����key</param>
	/// <param name="elapsedTime">�o�ߎ���</param>
	/// <returns>-1 : �Ȃ� ����ȊO : -1�ȊO</returns>
	int GetAnimation(const std::string& key,const double& elapsedTime);
	/// <summary>
	/// �o�^����Ă���A�j���[�V�����̃X�e�[�^�X��ς���
	/// </summary>
	/// <param name="key"></param>
	/// <param name="state"></param>
	/// <returns></returns>
	bool SetState(const std::string& key, const Animation_State& state, const double& nowElapsedTime);
private:
	AnimationManager();
	~AnimationManager();

	/// <summary>
	/// �J�X�^���f���[�^�[
	/// </summary>
	struct AnimationManagerDeleter
	{
		void operator()(AnimationManager* manager)
		{
			delete manager;
		}
	};


	std::map<Animation_State, std::string> stateMap_;									// �X�e�[�^�X�ʃA�j���[�V�����ɃA�N�Z�X���邽�߂̃}�b�v
	std::map<std::string, Animation> animMap_;											// AddAnimation�œo�^����key���g��

	static std::unique_ptr<AnimationManager, AnimationManagerDeleter> sInstance_;		// ����
};

