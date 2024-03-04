#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "core/object/ref_counted.h"

class TestClass : public RefCounted {
	GDCLASS(TestClass, RefCounted);

protected:
	static void _bind_methods();

public:
	int testreturnplusfive(int p_value);

	TestClass();
};

#endif
