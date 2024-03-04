#include "register_types.h"

#include "core/object/class_db.h"
#include "testclass.h"

void initialize_roguecardmod_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	GDREGISTER_CLASS(TestClass);
	//ClassDB::register_class<TestClass>();
}

void uninitialize_roguecardmod_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	// Nothing to do here in this example.
}