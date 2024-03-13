#ifndef GRID
#define GRID

#include "scene/3d/node_3d.h"
#include "core/variant/array.h"
#include "core/variant/dictionary.h"

class GridObject;

class Grid : public Node3D {
	GDCLASS(Grid, Node3D);

private:
	Dictionary GridData;
	Vector2 SquareSize;

protected:
	static void _bind_methods();

public:
	Grid();
	Dictionary get_raw_grid_data() const;

	Vector2 get_square_size() const;
	void set_square_size(const Vector2 &size);
	Vector3 get_square_size_3d() const;

	GridObject* get_cell_data(const Vector2i &location);
	ObjectID get_cell_ID(const Vector2i &location);
	void empty_cell_data(const Vector2i &location);
	void force_set_cell_data(const Vector2i &location, const ObjectID data);
	bool try_set_cell_data(const Vector2i &location, const ObjectID data);

	bool exists_on_grid(const ObjectID data);
	bool empty_grid();
	void load_grid(const Grid* source_grid);
};

#endif