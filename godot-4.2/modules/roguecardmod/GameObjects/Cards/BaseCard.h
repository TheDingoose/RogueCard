#pragma once

#ifndef BASECARD_H
#define BASECARD_H

#include "core/object/object.h"
#include "scene/2d/node_2d.h"

class Grid;

class BaseCard : public Resource
{
	GDCLASS(BaseCard, Resource);

private:
	int m_Cost;
	String m_Card_Description;
	//Node2D* m_Card; // This will be a custom card class, that will constructed within this class.
					  // This will be done through a series of enums that should be set through the sidebar.
					  // Think about attack, mobility, armor or utility cards. Class and damage type

protected:
	static void _bind_methods();

public:

	BaseCard();

	bool Use(Vector2i location, Grid *grid);

	void Set_Card_Cost(int a_cost) { m_Cost = a_cost; }
	int Get_Card_Cost() { return m_Cost; }

	void Set_Card_Description(String a_description) { m_Card_Description = a_description; }
	String Get_Card_Description() { return m_Card_Description; }
};

#endif
