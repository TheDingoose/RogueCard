#ifndef GRID
#define GRID

#include "scene/3d/node_3d.h"
#include "core/variant/array.h"

class Grid : public Node3D {
	GDCLASS(Grid, Node3D);

private:

//fill with an empty object, or nullpointers?
	//TypedArray<TypedArray<Object*>> GridData;

	Vector<Variant> GridData;
	Vector2i GridSize;

protected:
	static void _bind_methods();
//Inherit from node3d, Let thing assign themselves on grid, check the grid for what is there, and generally store data here
//Do we let the grid check AOEs too? probably not..
//EnsureGrid() Somewhere??

public:
	Grid();
	//bool instantiate_grid(Vector2i size);
	bool instantiate_grid(unsigned int size_x, unsigned int size_y);
	bool empty_grid();
	Vector2i get_grid_size();
	//Object* get_cell_data(Vector2i size);
	Variant get_cell_data(unsigned int x, unsigned int y);

	//

};

#endif
