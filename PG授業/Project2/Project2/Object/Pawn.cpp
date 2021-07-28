#include "Pawn.h"
#include "../Input/Keyboard.h"
#include "../Input/Gamepad.h"
#include "../TimeManager.h"

#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"

std::map<std::string, InputID> Pawn::keyMap_;

Pawn::Pawn(Potision2f& pos, Vector2f& speed, ControllType& type,TeamTag& tag) :Object(pos, speed, ObjectType::Pawn, tag)
{
	animState_ = Anim_State::Normal;
	alive_ = true;
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
		CommandData cmdData{};

		std::string name = command->first_attribute("name")->value();
		std::string allTime = command->first_attribute("allTime")->value();
		std::string reset = command->first_attribute("reset")->value();
		TRACE(name.c_str());
		TRACE("\n");
		// コマンド名と全体許容時間格納
		cmdData.name_ = name;
		cmdData.allTime_ = atof(allTime.c_str());
		cmdData.reset_ = atoi(reset.c_str());
		for (auto data = command->first_node("data"); data != nullptr; data = data->next_sibling())
		{
			std::string num = data->first_attribute("num")->value();
			std::string time = data->first_attribute("time")->value();
			TRACE(num.c_str());
			TRACE(" , ");
			TRACE(time.c_str());
			TRACE("\n");

			// コマンドIDの値と各IDの許容時間の値を追加
			cmdData.input_.push_back({ static_cast<unsigned int>(atoi(num.c_str())), atof(time.c_str()) });
		}
		TRACE("\n");

		commandList_.push_back(cmdData);
	}

}

std::list<std::string>& Pawn::GetAttackList(void)
{
	return attackList_;
}

const InstanceMap& Pawn::GetInstanceFuncMap() const
{
	return instanceMap_;
}

bool Pawn::Continue(void)
{
	return false;
}

void Pawn::Damage(int& value)
{
	hp_ -= value;
	animState_ = hp_ > 0 ? Anim_State::Dmage : Anim_State::Death;
}
