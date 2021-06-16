#pragma once
#include <map>
#include <string>
#include <vector>
#include "Vector2.h"

// rappidXml
#include "../TileMap/rapidxml.hpp"
#include "../TileMap/rapidxml_utils.hpp"

struct AnimData
{
	std::string animState;
	std::vector<int> chipData;
	std::vector<int> intervalData;
	int loop;
};

struct ImageData
{
	std::string imageName;			// 画像の名前
	Size imageSize;					// 全体のサイズ
	Size imageDivSize;				// 分割情報
};

using AnimDataVec = std::vector<AnimData>;

class TmxAnimation
{
public:
	TmxAnimation(std::string fileName);
	~TmxAnimation();

	bool LoadTmx(std::string fileName);

private:
	std::map<std::string, int>version_;

	std::string tmxFileName_;										// Tmxファイル名保存
	std::string tsxFileName_;										// Tsxファイル名保存

	AnimDataVec animVec_;
	ImageData imageData_;

	rapidxml::xml_document<> docment;
};

