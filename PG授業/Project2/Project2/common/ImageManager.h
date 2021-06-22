#pragma once
#include <memory>
#include <map>
#include <string>
#include <vector>
#include "Vector2.h"

#define lpImageManager ImageManager::GetInstance()

class ImageManager
{
public:
	/// <summary>
	/// ���̂̎擾
	/// </summary>
	/// <returns>���̂��Ԃ�</returns>
	static ImageManager& GetInstance()
	{
		return *sInstance_;
	}
	/// <summary>
	/// �C���[�W�̃n���h���擾
	/// �p�X�͈����ɏ����Ȃ��Ă���
	/// </summary>
	/// <param name="name">�t�@�C����+�`��</param>
	/// <returns>�n���h��</returns>
	const std::vector<int>& GetImageHandle(const std::string& name);
	/// <summary>
	/// �C���[�W�̃n���h���擾
	/// �p�X�͈����ɏ����Ȃ��Ă���
	/// </summary>
	/// <param name="name">�t�@�C�����ƌ`��</param>
	/// <param name="num">������</param>
	/// <param name="size">���������摜�̃T�C�Y</param>
	/// <returns>�n���h��</returns>
	const std::vector<int>& GetImageHandle(const std::string& name, const Size& num, const Size& size);

	const std::vector<int>& GetImageHandle(const std::string& name, const Size& num);

	/// <summary>
	/// �摜�T�C�Y���擾����
	/// �������A�o�^�ς݉摜�̂ݎ擾�ł���
	/// </summary>
	/// <param name="name">�t�@�C�����ƌ`��</param>
	/// <returns>�傫��</returns>
	const Size GetImageSize(const std::string& name);
private:
	ImageManager();
	~ImageManager();

	/// <summary>
	/// �J�X�^���f���[�^�[
	/// </summary>
	struct ImageManagerDeleter
	{
		void operator()(ImageManager* manager)
		{
			delete manager;
		}
	};

	static std::unique_ptr<ImageManager, ImageManagerDeleter> sInstance_;		// ����

	std::map<std::string, std::vector<int>> imageID_;							// �摜ID
};

