#include "ImageManager.h"
#include <DxLib.h>
#include <cassert>

std::unique_ptr<ImageManager, ImageManager::ImageManagerDeleter>ImageManager::sInstance_(new ImageManager);

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
}

const std::vector<int>& ImageManager::GetImageHandle(const std::string& name)
{
	// キーがないかチェックする
	if (imageID_.find(name) == imageID_.end())
	{
		std::string fileName = ("Resource/Image/" + name);
		int handle = LoadGraph(fileName.c_str());

		if (handle == -1)
		{
			// 失敗
			assert(!"画像読み込みエラー");
		}
		// 新しく追加
		imageID_[name].emplace_back(handle);
	}
	return imageID_[name];
}

const std::vector<int>& ImageManager::GetImageHandle(const std::string& name, const Size& num, const Size& size)
{
	// キーがないかチェックする
	if (imageID_.find(name) == imageID_.end())
	{
		std::string fileName = ("Resource/Image/" + name);
		auto allSize = num.x_ * num.y_;

		imageID_[name].resize(allSize);
		int tmpNum = LoadDivGraph(fileName.c_str(), allSize, num.x_, num.y_, size.x_, size.y_, imageID_[name].data());

		if (tmpNum == -1)
		{
			// 失敗
			assert(!"画像読み込みエラー");
		}
	}
	return imageID_[name];
}

const std::vector<int>& ImageManager::GetImageHandle(const std::string& name, const Size& num)
{
	// キーがないかチェックする
	if (imageID_.find(name) == imageID_.end())
	{
		std::string fileName = ("Resource/Image/" + name);
		auto allSize = num.x_ * num.y_;

		imageID_[name].resize(allSize);
		int handle = LoadGraph(fileName.c_str());
		if (handle == -1)
		{
			// 失敗
			assert(!"画像読み込みエラー" + name.c_str());
		}

		Size graphSize;
		GetGraphSize(handle,&graphSize.x_, &graphSize.y_);
		int tmpNum = LoadDivGraph(fileName.c_str(), allSize, num.x_, num.y_, graphSize.x_ / num.x_, graphSize.y_ / num.y_, imageID_[name].data());

		if (tmpNum == -1)
		{
			// 失敗
			assert(!"画像読み込みエラー" + name.c_str());
		}
	}
	return imageID_[name];
}

const Size ImageManager::GetImageSize(const std::string& name)
{
	Size size{ 0,0 };
	// キーがないかチェックする
	if (imageID_.find(name) == imageID_.end())
	{
		GetGraphSize(imageID_[name][0], &size.x_, &size.y_);
	}
	return size;
}
