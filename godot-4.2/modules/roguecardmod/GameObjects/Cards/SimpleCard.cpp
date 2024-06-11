#include "SimpleCard.h"

void SimpleCard::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_effect_array"), &SimpleCard::Get_Effect_Array);
	ClassDB::bind_method(D_METHOD("set_effect_array", "array"), &SimpleCard::Set_Effect_Array);
	ClassDB::add_property("SimpleCard", PropertyInfo(Variant::ARRAY, "effect"), "set_effect_array", "get_effect_array");
}

Array SimpleCard::Get_Effect_Array() const
{
	return m_effects;
}

void SimpleCard::Set_Effect_Array(const Array a_array)
{
	m_effects = a_array;
}
