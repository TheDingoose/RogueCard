#ifndef CARDEFFECT_H
#define CARDEFFECT_H

#include "core/object/object.h"
#include "scene/2d/node_2d.h"

enum EffectType
{
	ET_Attack = 0,
	ET_Defend,
	ET_Move,
	ET_Buff,
	ET_Debuff,
	ET_Debug
};

class CardEffect : public Resource
{
	GDCLASS(CardEffect, Resource);

private:
	int m_effect_strength;
	EffectType m_effect;

protected:
	static void _bind_methods();

public:
	CardEffect();

	int Get_Effect_Strength() const;
	void Set_Effect_Strength(const int a_strength);
	int Get_Effect_Enum() const;
	void Set_Effect_Enum(const int a_enum);
	

};


#endif
