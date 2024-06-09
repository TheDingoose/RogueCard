#include "CardEffect.h"

void CardEffect::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("Get_Effect_Strength"), &CardEffect::Get_Effect_Strength);
	ClassDB::bind_method(D_METHOD("Set_Effect_Strength"), &CardEffect::Set_Effect_Strength);
	ClassDB::bind_method(D_METHOD("Get_Effect_Enum"), &CardEffect::Get_Effect_Enum);
	ClassDB::bind_method(D_METHOD("Set_Effect_Enum"), &CardEffect::Set_Effect_Enum);
	ClassDB::add_property("CardEffect", PropertyInfo(Variant::INT, "effect_strength"), "Set_Effect_Strength", "Get_Effect_Strength");
	//ClassDB::add_property("CardEffect", PropertyInfo(Variant::INT, "effect"), "Set_Effect_Enum", "Get_Effect_Enum");

	
	ClassDB::add_property("CardEffect", PropertyInfo(Variant::INT, "effect", PROPERTY_HINT_ENUM, "Attack, Defend, Move, Buff, Debuff, Debug"), "Set_Effect_Enum", "Get_Effect_Enum");
}

CardEffect::CardEffect()
{
	m_effect = ET_Debug;
	m_effect_strength = 999;
}

int CardEffect::Get_Effect_Strength() const
{
	return m_effect_strength;
}

void CardEffect::Set_Effect_Strength(const int a_strength)
{
	m_effect_strength = a_strength;
}

int CardEffect::Get_Effect_Enum() const
{
	return (int)m_effect;
}

void CardEffect::Set_Effect_Enum(const int a_enum)
{
	m_effect = (EffectType)a_enum;
}
