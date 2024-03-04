#include "testclass.h"

int TestClass::testreturnplusfive(int p_value) {
	return p_value + 5;
}

TestClass::TestClass() {
	
}

void TestClass::_bind_methods() {
	ClassDB::bind_method(D_METHOD("testreturnplusfive", "value"), &TestClass::testreturnplusfive);
}

