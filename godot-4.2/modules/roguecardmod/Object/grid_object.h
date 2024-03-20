#ifndef GRID_OBJECT
#define GRID_OBJECT

#include "scene/3d/node_3d.h"
class Grid;

class GridObject : public Node3D {
	GDCLASS(GridObject, Node3D);

private:

	Vector2i GridPos;
	ObjectID LastGridSetID;

	//Validate the global grid, call only at runtime
	bool validate_grid();
	//Make sure that this object exists where it thinks it does on the grid
	bool validate_exists_on_grid_pos(Vector2i location, Grid *grid);
	//Set this nodes transform to where it should be on the grid
	void move_to_grid_position(Grid *grid);

	Grid *find_grid_in_scene();

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:

	Vector2i get_grid_pos() const;

	void set_on_grid(Vector2i location, Grid *grid);
	void remove_from_grid(Grid *grid);
	void move_on_grid(Vector2i location, Grid *grid);
	bool safe_move_on_grid(Vector2i location, Grid *grid);

	GridObject();
	//Destructor, get yourself off the grid
	~GridObject();
};

#endif
