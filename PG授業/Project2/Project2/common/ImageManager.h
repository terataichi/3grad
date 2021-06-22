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
	/// 実体の取得
	/// </summary>
	/// <returns>実体が返る</returns>
	static ImageManager& GetInstance()
	{
		return *sInstance_;
	}
	/// <summary>
	/// イメージのハンドル取得
	/// パスは引数に書かなくていい
	/// </summary>
	/// <param name="name">ファイル名+形式</param>
	/// <returns>ハンドル</returns>
	const std::vector<int>& GetImageHandle(const std::string& name);
	/// <summary>
	/// イメージのハンドル取得
	/// パスは引数に書かなくていい
	/// </summary>
	/// <param name="name">ファイル名と形式</param>
	/// <param name="num">分割数</param>
	/// <param name="size">分割される画像のサイズ</param>
	/// <returns>ハンドル</returns>
	const std::vector<int>& GetImageHandle(const std::string& name, const Size& num, const Size& size);

	const std::vector<int>& GetImageHandle(const std::string& name, const Size& num);

	/// <summary>
	/// 画像サイズを取得する
	/// ただし、登録済み画像のみ取得できる
	/// </summary>
	/// <param name="name">ファイル名と形式</param>
	/// <returns>大きさ</returns>
	const Size GetImageSize(const std::string& name);
private:
	ImageManager();
	~ImageManager();

	/// <summary>
	/// カスタムデリーター
	/// </summary>
	struct ImageManagerDeleter
	{
		void operator()(ImageManager* manager)
		{
			delete manager;
		}
	};

	static std::unique_ptr<ImageManager, ImageManagerDeleter> sInstance_;		// 実体

	std::map<std::string, std::vector<int>> imageID_;							// 画像ID
};

