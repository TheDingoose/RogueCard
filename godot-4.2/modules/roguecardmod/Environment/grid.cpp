#include "grid.h"

#include "../Object/grid_object.h"

Grid::Grid() {
	
	SquareSize = Vector2(1,1);
}

Vector2 Grid::get_square_size() const {
	return SquareSize; //Update all childrens positions??
}

void Grid::set_square_size(const Vector2 &size) {
	SquareSize = size;
}

Variant Grid::get_cell_data(const Vector2i &location) {
	//is_instance_valid( object )
	return GridData[location];
}

void Grid::empty_cell_data(const Vector2i &location) {
	GridData.erase(location);
	return;
}

void Grid::force_set_cell_data(const Vector2i &location, const Variant &data) {
	GridData[location] = data;
	return;
}

//Check if a cell is occupied, if so, return false, otherwise set it and resturn true
bool Grid::try_set_cell_data(const Vector2i &location, const Variant &data) {
	if (GridData.get_valid(location)) {
		printf("Found something");
		return false;
	} else {
		printf("Not found something");
		GridData[location] = data;
		return true;
	}
	return false;
}

//empty, but keep size
bool Grid::empty_grid() {
	//Do we need to run destructors??
	GridData.clear();
	return true;
}

void Grid::_bind_methods() {
	ClassDB::bind_method(D_METHOD("empty grid"), &Grid::empty_grid);
	ClassDB::bind_method(D_METHOD("get cell data", "location"), &Grid::get_cell_data, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("empty cell data", "location"), &Grid::empty_cell_data, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("force set cell data", "location", "data"), &Grid::force_set_cell_data);
	ClassDB::bind_method(D_METHOD("try set cell data", "location", "data"), &Grid::try_set_cell_data);
	ClassDB::bind_method(D_METHOD("get square size"), &Grid::get_square_size);
	ClassDB::bind_method(D_METHOD("set square size", "size"), &Grid::set_square_size);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "square size"), "set square size", "get square size");
}
