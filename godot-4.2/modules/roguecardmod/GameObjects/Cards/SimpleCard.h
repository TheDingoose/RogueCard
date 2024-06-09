#ifndef SIMPLECARD_H
#define SIMPLECARD_H

#include "BaseCard.h"	

class SimpleCard : public BaseCard
{
	GDCLASS(SimpleCard, BaseCard);

private:

	Array m_effects;

protected:

	static void _bind_methods();

public:

	Array Get_Effect_Array() const;
	void Set_Effect_Array( const Array a_array);

};

#endif // SimpleCard
