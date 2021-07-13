#include "Pawn.h"
#include "../Input/Keyboard.h"
#include "../Input/Gamepad.h"
#include "../TimeManager.h"

#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"

std::map<std::string, InputID> Pawn::keyMap_;

Pawn::Pawn(Potision2f& pos, Vector2f& speed, ControllType& type) :Object(pos, speed)
{
	state_ = Anim_State::Normal;

	keyMap_.try_emplace( "Left",InputID::Left );
	keyMap_.try_emplace("Right", InputID::Right);
	keyMap_.try_emplace("Down", InputID::Down);
	keyMap_.try_emplace("Up", InputID::Up);


	// コントローラーの設定
	if (type == ControllType::GamePad)
	{
		controller_ = std::make_unique<Gamepad>();
		return;
	}
	controller_ = std::make_unique<Keyboard>();
}

Pawn::~Pawn()
{
}

void Pawn::CommandBufUpdate(void)
{

}

void Pawn::LoadStateModule(std::string&& fileName)
{
	rapidxml::file<> moduleFileName = fileName.c_str();
	stateVec_ = moduleFileName.vecData();
	stateDoc.parse<0>(stateVec_.data());
	stateNode_ = stateDoc.first_node("moduleList");
}

void Pawn::LoadCommandList(std::string&& fileName)
{
	rapidxml::file<> file = fileName.c_str();
	rapidxml::xml_document<> docment;
	docment.parse<0>(file.data());

	rapidxml::xml_node<>* node;
	node = docment.first_node("commandList");

	std::string str = node->first_attribute("name")->value();
	TRACE(str.c_str());
	TRACE("\n");

	for (auto command = node->first_node(); command != nullptr; command = command->next_sibling())
	{
		std::string str = command->first_attribute("name")->value();
		TRACE(str.c_str());
		TRACE("\n");
		for (auto data = command->first_node("data"); data != nullptr; data = data->next_sibling())
		{
			std::string datas = data->first_attribute("num")->value();
			TRACE(datas.c_str());
			TRACE("\n");
		}
		TRACE("\n");
	}
}
