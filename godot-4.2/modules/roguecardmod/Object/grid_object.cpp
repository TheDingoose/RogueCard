#include "grid_object.h"

#include "../Environment/grid.h"

GridObject::GridObject() {
	LastGridSet = nullptr;
}

GridObject::~GridObject() {
	if (LastGridSet != nullptr && validate_exists_on_grid_pos(GridPos, LastGridSet)) {
		LastGridSet->empty_cell_data(GridPos);
	}
	LastGridSet = nullptr;
}

bool GridObject::validate_grid() {
	ERR_FAIL_COND_V_MSG(Object::cast_to<Grid>(get_node_or_null(NodePath("/root/GlobalGrid"))) == nullptr, false, "Tried grid access not at runtime!");
	return true;
}

bool GridObject::validate_exists_on_grid_pos(Vector2i location, Grid *grid) {
	GridObject *data = grid->get_cell_data(location);
	
	if (data != nullptr) {
		return data->get_instance_id() == get_instance_id();
	}
	return false;
}

void GridObject::move_to_grid_position(Grid *grid) {
	if (grid->exists_on_grid(get_instance_id())) {
		Vector3 GridPosFloat(GridPos.x, 0, GridPos.y);
		set_global_position(grid->get_global_position() + GridPosFloat * grid->get_square_size_3d());
	}
}

Vector2i GridObject::get_grid_pos() const {
	return GridPos;
}

void GridObject::set_on_grid(Vector2i location, Grid *grid) {
	grid->force_set_cell_data(location, get_instance_id());
	GridPos = location;
	LastGridSet = grid;
	move_to_grid_position(grid);
}

void GridObject::remove_from_grid(Grid *grid) {
	if (grid->exists_on_grid(get_instance_id())) {
		grid->empty_cell_data(GridPos);
		LastGridSet = nullptr;
	}
}

void GridObject::move_on_grid(Vector2i location, Grid *grid) {
	if (grid->exists_on_grid(get_instance_id())) {
		remove_from_grid(grid);
		set_on_grid(location, grid);
	}
}

bool GridObject::safe_move_on_grid(Vector2i location, Grid *grid) {
	if (validate_exists_on_grid_pos(GridPos, grid)) {
		if (grid->try_set_cell_data(location, get_instance_id())) {
			grid->empty_cell_data(GridPos);
			GridPos = location;
			LastGridSet = grid;
			move_to_grid_position(grid);
			return true;
		}
		print_line("SAFEMOVE: Cell was occupied when trying to move " + get_name());
		return false;
	} else {
		print_line("SAFEMOVE: Didnt find on own location " + get_name());
		return false;
	}
}

void GridObject::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_on_grid", "location", "grid"), &GridObject::set_on_grid);
	ClassDB::bind_method(D_METHOD("remove_from_grid", "grid"), &GridObject::remove_from_grid);
	ClassDB::bind_method(D_METHOD("move_on_grid", "location", "grid"), &GridObject::move_on_grid);
	ClassDB::bind_method(D_METHOD("safe_move_on_grid", "location", "grid"), &GridObject::safe_move_on_grid);
	ClassDB::bind_method(D_METHOD("move_to_grid_position", "grid"), &GridObject::move_to_grid_position);
	ClassDB::bind_method(D_METHOD("get_grid_pos"), &GridObject::get_grid_pos);
}
