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
}
