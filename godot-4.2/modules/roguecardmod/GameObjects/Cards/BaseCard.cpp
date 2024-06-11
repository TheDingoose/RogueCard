#include "BaseCard.h"

#include "../../Environment/grid.h"

BaseCard::BaseCard()
{
	//m_Card = nullptr;
	m_Cost = 0;

}

bool BaseCard::Use(Vector2i location, Grid *grid) {
	return false;
}


void BaseCard::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("use_card", "location", "grid"), &BaseCard::Use);
	ClassDB::bind_method(D_METHOD("set_card_cost"), &BaseCard::Set_Card_Cost);
	ClassDB::bind_method(D_METHOD("get_card_cost"), &BaseCard::Get_Card_Cost);

	ClassDB::add_property("BaseCard", PropertyInfo(Variant::INT, "cost"), "set_card_cost", "get_card_cost");

	ClassDB::bind_method(D_METHOD("set_card_description"), &BaseCard::Set_Card_Description);
	ClassDB::bind_method(D_METHOD("get_card_description"), &BaseCard::Get_Card_Description);

	ClassDB::add_property("BaseCard", PropertyInfo(Variant::STRING, "description"), "set_card_description", "get_card_description");

}
