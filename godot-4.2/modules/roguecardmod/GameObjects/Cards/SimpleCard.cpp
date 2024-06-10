#include "SimpleCard.h"

void SimpleCard::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("Get_Effect_Array"), &SimpleCard::Get_Effect_Array);
	ClassDB::bind_method(D_METHOD("Set_Effect_Array"), &SimpleCard::Set_Effect_Array);
	ClassDB::add_property("SimpleCard", PropertyInfo(Variant::ARRAY, "Effect"), "Set_Effect_Array", "Get_Effect_Array");
}

Array SimpleCard::Get_Effect_Array() const
{
	return m_effects;
}

void SimpleCard::Set_Effect_Array(const Array a_array)
{
	m_effects = a_array;
}
