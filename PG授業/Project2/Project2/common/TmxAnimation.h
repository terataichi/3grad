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
	std::string imageName;			// �摜�̖��O
	Size imageSize;					// �S�̂̃T�C�Y
	Size imageDivSize;				// �������
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

	std::string tmxFileName_;										// Tmx�t�@�C�����ۑ�
	std::string tsxFileName_;										// Tsx�t�@�C�����ۑ�

	AnimDataMap animMap_;
	AnimImageData imageData_;

	rapidxml::xml_document<> docment;
};

