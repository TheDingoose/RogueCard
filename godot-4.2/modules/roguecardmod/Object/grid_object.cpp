#include "grid_object.h"

#include "../Environment/grid.h"

Grid* FindGrid(Node* n) {
	for (int i = 0; i < n->get_child_count(); i++) {
		if (Grid* b = Object::cast_to<Grid>(n->get_child(i))) {
			return b;
		}
		else {
			Grid* p = FindGrid(n->get_child(i));
			if (p != nullptr) {
				return p;
			}
		}
	}
	return nullptr;
}

GridObject::GridObject() {

#ifdef TOOLS_ENABLED
	set_notify_transform(true);
#endif
	
}

GridObject::~GridObject() {

	//we need to do this to make sure the object was not already deleted. I ran into problems when the engine was emptying its undo/redo cache
	Object *TestPointer = ObjectDB::get_instance(LastGridSetID);
	if (TestPointer == nullptr) {
		return;
	}

	Grid *GridPointer = Object::cast_to<Grid>(TestPointer);

	if (validate_exists_on_grid_pos(GridPos, GridPointer)) {
		GridPointer->empty_cell_data(GridPos);
	}
	GridPointer = nullptr;
	TestPointer = nullptr;
}

void GridObject::_notification(int p_what) {
	Node3D::_notification(p_what);
#ifdef TOOLS_ENABLED
	switch (p_what) {
		case NOTIFICATION_TRANSFORM_CHANGED: {
			ERR_THREAD_GUARD;

			//Check if we are already moving on a grid, if not, find the very first one in the scene tree, and set self down on it
			if (!LastGridSetID.is_valid()) {
				print_line("Couldnt Find LastGridSet on Notif Transform Changed " + get_name());
				Grid* FoundGrid = find_grid_in_scene();
				if (FoundGrid == nullptr) {
					print_line("Couldnt Find Any grid in scene on Notif Transform Changed " + get_name());
				break;
				};
				LastGridSetID = FoundGrid->get_instance_id();
			}

			Grid *LastGrid = Object::cast_to<Grid>(ObjectDB::get_instance(LastGridSetID));
			Vector2 GlobalPos(get_global_position().x, get_global_position().z);
			Vector3 GridPosFloat(GridPos.x, 0, GridPos.y);
			Vector3 GridPosWorldSpace(LastGrid->get_global_position() + GridPosFloat * LastGrid->get_square_size_3d());


			//Check if it moved we need to change the registered position of the object
			if (((GridPosWorldSpace * Vector3(1, 0, 1)) - (get_global_position() * Vector3(1, 0, 1))).length()
			>= MIN(LastGrid->get_square_size().x, LastGrid->get_square_size().y)) {
				safe_move_on_grid((GlobalPos / LastGrid->get_square_size()).round(), LastGrid);
			}
		}
	}
#endif // TOOLS_ENABLED
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

Grid *GridObject::find_grid_in_scene() {
	return FindGrid(get_tree()->get_edited_scene_root());
}

Vector2i GridObject::get_grid_pos() const {
	return GridPos;
}

void GridObject::set_on_grid(Vector2i location, Grid *grid) {
	grid->force_set_cell_data(location, get_instance_id());
	GridPos = location;
	LastGridSetID = grid->get_instance_id();
	move_to_grid_position(grid);
}

void GridObject::remove_from_grid(Grid *grid) {
	if (grid->exists_on_grid(get_instance_id())) {
		grid->empty_cell_data(GridPos);
		LastGridSetID = ObjectID();
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
		grid->empty_cell_data(GridPos);
	} else {
		print_line("SAFEMOVE: Didnt find on own location, Setting instead " + get_name());
	}

	if (grid->try_set_cell_data(location, get_instance_id())) {
		GridPos = location;
		LastGridSetID = grid->get_instance_id();
		move_to_grid_position(grid);
		return true;
	}

	print_line("SAFEMOVE: Cell was occupied when trying to move " + get_name());
	return false;
}

void GridObject::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_on_grid", "location", "grid"), &GridObject::set_on_grid);
	ClassDB::bind_method(D_METHOD("remove_from_grid", "grid"), &GridObject::remove_from_grid);
	ClassDB::bind_method(D_METHOD("move_on_grid", "location", "grid"), &GridObject::move_on_grid);
	ClassDB::bind_method(D_METHOD("safe_move_on_grid", "location", "grid"), &GridObject::safe_move_on_grid);
	ClassDB::bind_method(D_METHOD("move_to_grid_position", "grid"), &GridObject::move_to_grid_position);
	ClassDB::bind_method(D_METHOD("get_grid_pos"), &GridObject::get_grid_pos);
}
