#include "BaseCard.h"



BaseCard::BaseCard()
{
	m_Card = nullptr;
	m_Cost = 0;

}

bool BaseCard::Use()
{
	return false;
}


void BaseCard::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("Use card"), &BaseCard::Use);
	ClassDB::bind_method(D_METHOD("Set card cost"), &BaseCard::Set_Card_Cost);
	ClassDB::bind_method(D_METHOD("Get card cost"), &BaseCard::Get_Card_Cost);
}
