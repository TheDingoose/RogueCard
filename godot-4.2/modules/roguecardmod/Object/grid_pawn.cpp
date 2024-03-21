#include "grid_pawn.h"

GridPawn::GridPawn() {
	MaxHealth = 0;
	Health = 0;
	Armor = 0;
	Team = 0;
}

void GridPawn::turn_start() {

}

void GridPawn::turn_end() {

}

void GridPawn::change_max_health(int change) {
	MaxHealth += change;
	Health = fmin(MaxHealth, Health);
}

void GridPawn::change_health(int change) {
	Health += change;
}

void GridPawn::change_armor(int change) {
	Armor += change;
}

void GridPawn::set_status(HashMap<StatusEffect, int> status) {
	StatusEffects = status;
}

HashMap<StatusEffect, int> GridPawn::get_status() {
	return StatusEffects;
}

void GridPawn::apply_status(StatusEffect effect, int intensity) {
	if (StatusEffects.has(effect)) {
		StatusEffects[effect] += intensity; //Is this the math we want for adding intensity
	} else {
		StatusEffects[effect] = intensity;
	}
}

void GridPawn::remove_status(StatusEffect effect) {
	StatusEffects.erase(effect);
}

void GridPawn::death() {
}

void GridPawn::_bind_methods() {
	ClassDB::bind_method(D_METHOD("turn_start"), &GridPawn::turn_start);
	ClassDB::bind_method(D_METHOD("turn_end"), &GridPawn::turn_end);
	ClassDB::bind_method(D_METHOD("set_max_health", "amount"), &GridPawn::set_max_health);
	ClassDB::bind_method(D_METHOD("get_max_health"), &GridPawn::get_max_health);
	ClassDB::bind_method(D_METHOD("set_health", "amount"), &GridPawn::set_health);
	ClassDB::bind_method(D_METHOD("get_health"), &GridPawn::get_health);
	ClassDB::bind_method(D_METHOD("set_armor", "amount"), &GridPawn::set_armor);
	ClassDB::bind_method(D_METHOD("get_armor"), &GridPawn::get_armor);
	ClassDB::bind_method(D_METHOD("set_team", "amount"), &GridPawn::set_team);
	ClassDB::bind_method(D_METHOD("get_team"), &GridPawn::get_team);
	ClassDB::bind_method(D_METHOD("change_max_health", "amount"), &GridPawn::change_max_health);
	ClassDB::bind_method(D_METHOD("change_health", "amount"), &GridPawn::change_health);
	ClassDB::bind_method(D_METHOD("change_armor", "amount"), &GridPawn::change_armor);

	//GET THESE BACK IN, PROBABLY CHANGE THE STATUS STORING TYPE

	//ClassDB::bind_method(D_METHOD("set_status", "amount"), &GridPawn::set_status);
	//ClassDB::bind_method(D_METHOD("get_status"), &GridPawn::get_status);
	//ClassDB::bind_method(D_METHOD("apply_status", "effect", "intensity"), &GridPawn::get_status);
	//ClassDB::bind_method(D_METHOD("remove_status", "effect"), &GridPawn::get_status);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_health"), "set_max_health", "get_max_health");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "health"), "set_health", "get_health");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "armor"), "set_armor", "get_armor");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "team"), "set_team", "get_team");

	//ClassDB::bind_method(D_METHOD("remove_from_grid", "grid"), &GridObject::remove_from_grid);
	//ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "square_size"), "set_square_size", "get_square_size");
}
