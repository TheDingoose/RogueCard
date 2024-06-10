#include "BaseCard.h"



BaseCard::BaseCard()
{
	//m_Card = nullptr;
	m_Cost = 0;

}

bool BaseCard::Use()
{
	return false;
}


void BaseCard::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("Use_card"), &BaseCard::Use);
	ClassDB::bind_method(D_METHOD("Set_card_cost"), &BaseCard::Set_Card_Cost);
	ClassDB::bind_method(D_METHOD("Get_card_cost"), &BaseCard::Get_Card_Cost);

	ClassDB::add_property("BaseCard", PropertyInfo(Variant::INT, "Cost"), "Set_card_cost", "Get_card_cost");

	ClassDB::bind_method(D_METHOD("Set_Card_Description"), &BaseCard::Set_Card_Description);
	ClassDB::bind_method(D_METHOD("Get_Card_Description"), &BaseCard::Get_Card_Description);

	ClassDB::add_property("BaseCard", PropertyInfo(Variant::STRING, "Description"), "Set_Card_Description", "Get_Card_Description");

}
