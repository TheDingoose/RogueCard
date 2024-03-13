#include "grid.h"

#include "../Object/grid_object.h"

Grid::Grid() {
	
	SquareSize = Vector2(1,1);
}

Dictionary Grid::get_raw_grid_data() const{
	return GridData;
}

Vector2 Grid::get_square_size() const {
	return SquareSize; //Update all childrens positions??
}

void Grid::set_square_size(const Vector2 &size) {
	SquareSize = size;
}

Vector3 Grid::get_square_size_3d() const {
	return Vector3(SquareSize.x, 0, SquareSize.y);
}

GridObject* Grid::get_cell_data(const Vector2i &location) {
	if (GridData.get_valid(location)) {
		return Object::cast_to<GridObject>(ObjectDB::get_instance(GridData[location]));
	}
	return nullptr;
}

ObjectID Grid::get_cell_ID(const Vector2i &location) {
	return GridData[location];
}

void Grid::empty_cell_data(const Vector2i &location) {
	GridData.erase(location);
	return;
}

void Grid::force_set_cell_data(const Vector2i &location, const ObjectID data) {
	GridData[location] = data;
	
	return;
}

bool Grid::try_set_cell_data(const Vector2i &location, const ObjectID data) {
	//If there is already something registered in that position
	if (GridData.get_valid(location)) {
		return false;
	} else {
		GridData[location] = data;
		return true;
	}
	return false;
}

bool Grid::exists_on_grid(ObjectID data) {
	for (int i = 0; i < GridData.size(); i++) {
		if (GridData.values()[i] == data) {return true;}
	}
	
	return false;
}

bool Grid::empty_grid() {
	GridData.clear();
	return true;
}

void Grid::load_grid(const Grid* source_grid) {
	empty_grid();
	SquareSize = source_grid->SquareSize;

	//Not doing this, otherwise Objects cant destruct themselves properly
	//GridData = source_grid->get_raw_grid_data();

	//Instead we do
	List<Variant> KeyList;
	source_grid->get_raw_grid_data().get_key_list(&KeyList);
	for (int i = 0; i < KeyList.size(); i++) {
		//Forcing the Objects on the grid to register themselves so that their LastGridSet is set properly
		Object::cast_to<GridObject>(ObjectDB::get_instance(source_grid->get_raw_grid_data()[KeyList[i]]))->set_on_grid(KeyList[i], this);
	}

}

void Grid::_bind_methods() {
	ClassDB::bind_method(D_METHOD("empty_grid"), &Grid::empty_grid);
	ClassDB::bind_method(D_METHOD("load_grid", "source_grid"), &Grid::load_grid);
	ClassDB::bind_method(D_METHOD("exists_on_grid", "data"), &Grid::exists_on_grid);
	ClassDB::bind_method(D_METHOD("get_cell_data", "location"), &Grid::get_cell_data);
	ClassDB::bind_method(D_METHOD("get_cell_ID", "location"), &Grid::get_cell_ID);
	ClassDB::bind_method(D_METHOD("empty_cell_data", "location"), &Grid::empty_cell_data, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("force_set_cell_data", "location", "data"), &Grid::force_set_cell_data);
	ClassDB::bind_method(D_METHOD("try_set_cell_data", "location", "data"), &Grid::try_set_cell_data);
	ClassDB::bind_method(D_METHOD("get_square_size"), &Grid::get_square_size);
	ClassDB::bind_method(D_METHOD("set_square_size", "size"), &Grid::set_square_size);
	ClassDB::bind_method(D_METHOD("get_square_size_3d"), &Grid::get_square_size_3d);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "square_size"), "set_square_size", "get_square_size");
}
