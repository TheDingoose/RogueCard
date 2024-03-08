#ifndef GRID
#define GRID

#include "scene/3d/node_3d.h"
#include "core/variant/array.h"
#include "core/variant/dictionary.h"

class GridObject;

class Grid : public Node3D {
	GDCLASS(Grid, Node3D);

private:

//fill with an empty object, or nullpointers?
	//Vector<Variant> GridData;
	Dictionary GridData;
	Vector2 SquareSize;

protected:
	static void _bind_methods();
//Inherit from node3d, Let thing assign themselves on grid, check the grid for what is there, and generally store data here
//Do we let the grid check AOEs too? probably not..
//EnsureGrid() Somewhere??

public:
	Grid();

	Vector2 get_square_size() const;
	void set_square_size(const Vector2 &size);

	Variant get_cell_data(const Vector2i &location);
	void empty_cell_data(const Vector2i &location);
	void force_set_cell_data(const Vector2i &location, const Variant &data);
	bool try_set_cell_data(const Vector2i &location, const Variant &data);

	bool empty_grid();
	
	

};

#endif
