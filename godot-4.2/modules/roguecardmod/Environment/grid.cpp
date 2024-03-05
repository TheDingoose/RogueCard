#include "grid.h"



Grid::Grid() {
	GridSize = Vector2i(0,0);
}

//bool Grid::instantiate_grid(Vector2i size) {
//	return instantiate_grid(size.x, size.y);
//}

bool Grid::instantiate_grid(unsigned int size_x, unsigned int size_y) {
	GridSize = Vector2i(size_x, size_y);
	GridData.clear();
	GridData.resize(size_x * size_y);

	return true;
}

//empty, but keep size
bool Grid::empty_grid() {
	//Do we need to run destructors??
	instantiate_grid(GridSize.x, GridSize.y);
	return true;
}

Vector2i Grid::get_grid_size() {
	return GridSize;
}

//Object *Grid::get_cell_data(Vector2i size) {
//	return get_cell_data(size.x, size.y);
//}

Variant Grid::get_cell_data(unsigned int x, unsigned int y) {
	//is_instance_valid( object )
	ERR_FAIL_COND_V_MSG((x + y * GridSize.x) < GridSize.x * GridSize.y, 0 , vformat("Trying to get a point out of bounds!"));
	return GridData[x + y * GridSize.x];
}

void Grid::_bind_methods() {
	ClassDB::bind_method(D_METHOD("instantiate grid", "size_x", "size_y"), &Grid::instantiate_grid, DEFVAL(0), DEFVAL(0));
	ClassDB::bind_method(D_METHOD("empty grid"), &Grid::empty_grid);
	ClassDB::bind_method(D_METHOD("get grid size"), &Grid::get_grid_size);
	ClassDB::bind_method(D_METHOD("get cell data", "size_x", "size_y"), &Grid::get_cell_data, DEFVAL(0), DEFVAL(0));
}
