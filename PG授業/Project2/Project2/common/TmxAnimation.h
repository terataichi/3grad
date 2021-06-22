#pragma once
#include <map>
#include <string>
#include <vector>
#include "Vector2.h"

// rappidXml
#include "../TileMap/rapidxml.hpp"
#include "../TileMap/rapidxml_utils.hpp"

struct ChipData
{
	int chip;
	double interval;
};

struct AnimData
{
	std::string stateName;
	std::vector<ChipData> chipData;
	int loop;
};

struct AnimImageData
{
	std::string imageName;			// 画像の名前
	Size imageSize;					// 全体のサイズ
	Size imageDivSize;				// 分割情報
};

using AnimDataMap = std::map<std::string, AnimData>;

class TmxAnimation
{
public:
	TmxAnimation(std::string fileName);
	~TmxAnimation();

	bool LoadTmx(std::string fileName);
	const AnimDataMap& GetAnimData(void)const;
	const AnimImageData& GetImageData(void)const;
private:
	std::map<std::string, int>version_;

	std::string tmxFileName_;										// Tmxファイル名保存
	std::string tsxFileName_;										// Tsxファイル名保存

	AnimDataMap animMap_;
	AnimImageData imageData_;

	rapidxml::xml_document<> docment;
};

