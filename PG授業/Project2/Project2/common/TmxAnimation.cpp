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

    std::string str = root_node->first_attribute("imagePath")->value();
    imageData_.imageName = str.substr(str.find_first_of("C"));

    tmxFileName_ = fileName;
    //  ﾏｯﾌﾟの中身を保存
    for (rapidxml::xml_attribute<>* data = root_node->first_attribute();
        data != nullptr;
        data = data->next_attribute())
    {
        std::cout << data->name() << "[" << data->value() << "]" << std::endl;
    }



	return false;
}
