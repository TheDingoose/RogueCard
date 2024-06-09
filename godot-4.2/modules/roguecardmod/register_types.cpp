#include "register_types.h"

#include "core/object/class_db.h"
#include "testclass.h"
#include "Environment/grid.h"
#include "GameObjects/Cards/BaseCard.h"
#include "GameObjects/Cards/SimpleCard.h"
#include "GameObjects/Cards/CardEffect.h"
#include "Object/grid_object.h"
#include "Object/grid_pawn.h"

void initialize_roguecardmod_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	GDREGISTER_CLASS(TestClass);
	GDREGISTER_CLASS(Grid);
	GDREGISTER_CLASS(BaseCard);
	GDREGISTER_CLASS(SimpleCard);
	GDREGISTER_CLASS(CardEffect)
	GDREGISTER_CLASS(GridObject);
	GDREGISTER_CLASS(GridPawn);
	//ClassDB::register_class<TestClass>();
}

void uninitialize_roguecardmod_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	// Nothing to do here in this example.
}
