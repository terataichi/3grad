#include <type_traits>
#include "InputID.h"

InputID begin(InputID)
{
	return InputID::Up;
}

InputID end(InputID)
{
	return InputID::Max;
}

InputID operator++(InputID& id)
{
	return id = static_cast<InputID>(std::underlying_type<InputID>::type(id) + 1);
}

InputID operator*(InputID key)
{
	return key;
}
