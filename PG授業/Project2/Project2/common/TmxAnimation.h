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
	std::string imageName;			// �摜�̖��O
	Size imageSize;					// �S�̂̃T�C�Y
	Size imageDivSize;				// �������
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

	std::string tmxFileName_;										// Tmx�t�@�C�����ۑ�
	std::string tsxFileName_;										// Tsx�t�@�C�����ۑ�

	AnimDataVec animVec_;
	ImageData imageData_;

	rapidxml::xml_document<> docment;
};

