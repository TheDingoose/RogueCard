#pragma once

#ifndef BASECARD_H
#define BASECARD_H

#include "core/object/object.h"
#include "scene/2d/node_2d.h"


class BaseCard : public Object
{
	GDCLASS(BaseCard, Object);

private:
	int m_Cost;
	Node2D* m_Card; // This will be a custom card class, that will constructed within this class.
					// This will be done through a series of enums that should be set through the sidebar.
					// Think about attack, mobility, armor or utility cards. Class and damage type

protected:
	static void _bind_methods();

public:

	BaseCard();

	bool Use();

	void Set_Card_Cost(int a_cost) { m_Cost = a_cost; }
	int Get_Card_Cost() { return m_Cost; }
};

#endif
