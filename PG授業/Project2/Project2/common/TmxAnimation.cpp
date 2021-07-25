#include "TmxAnimation.h"
#include <iostream>
#include <sstream>
#include <cassert>

TmxAnimation::TmxAnimation(std::string fileName)
{
    version_.try_emplace("1.4", 1);
    version_.try_emplace("1.4.1", 1);
    version_.try_emplace("1.4.2", 1);
    version_.try_emplace("1.4.3", 1);

    LoadTmx(fileName);

}

TmxAnimation::~TmxAnimation()
{
}

bool TmxAnimation::LoadTmx(std::string fileName)
{
    rapidxml::file<> file(fileName.c_str());
    docment.parse<0>(file.data());

    rapidxml::xml_node<>* root_node;
    root_node = docment.first_node("source");

    // バージョンチェック
    if (version_.count(root_node->first_attribute("version")->value()) == 0) {
        assert(!"バージョンが対応していません");
        return false;
    }

    std::string str = root_node->first_attribute("imagepath")->value();
    imageData_.imageName = str.substr(str.find_first_of("e") + 1);
    imageData_.imageDivSize = { atoi(root_node->first_attribute("divwidth")->value()),atoi(root_node->first_attribute("divheight")->value()) };
    imageData_.imageSize = { atoi(root_node->first_attribute("chipsizeX")->value()),atoi(root_node->first_attribute("chipsizeY")->value()) };
    tmxFileName_ = fileName;
   
    for (rapidxml::xml_node<>* layer_node = root_node->first_node("state");
        layer_node != nullptr;
        layer_node = layer_node->next_sibling("state"))
    {
        AnimData layer;

        // 基本情報の格納
        layer.stateName = layer_node->first_attribute("name")->value();
        layer.loop = atoi(layer_node->first_attribute("loop")->value());

        // チップデータの格納
        rapidxml::xml_node<>* data_node = layer_node->first_node("data");
        std::string data = data_node->value();

        std::istringstream iss{ data };
        std::string num;

        auto size = atoi(layer_node->first_attribute("height")->value());
        layer.chipData.resize(size);
        //for (int i = 0; i <= layer.width * layer.heigth; i++)
        int i = 0;
        for (auto& data : layer.chipData)
        {
            getline(iss, num, ',');
            data.chip = atoi(num.c_str());
            getline(iss, num, ',');
            data.interval = static_cast<double>(atof(num.c_str()));
            i++;
        }

        // 情報の追加
        animMap_.try_emplace(layer.stateName, layer);
    }

	return false;
}

const AnimDataMap& TmxAnimation::GetAnimData(void) const
{
    return animMap_;
}

const AnimImageData& TmxAnimation::GetImageData(void) const
{
    return imageData_;
}
