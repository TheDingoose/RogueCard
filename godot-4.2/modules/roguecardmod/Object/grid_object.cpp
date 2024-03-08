#include "grid_object.h"

#include "../Environment/grid.h"

GridObject::GridObject() {
}

void GridObject::register_grid(Grid* grid) {
//grid->get_instance_id()
	GridPtr = std::shared_ptr<Grid>();
	ValidGrid = true;
}

void GridObject::_bind_methods() {
	ClassDB::bind_method(D_METHOD("register grid", "grid"), &GridObject::register_grid);
}


