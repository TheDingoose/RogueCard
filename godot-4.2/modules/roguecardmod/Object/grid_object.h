#ifndef GRID_OBJECT
#define GRID_OBJECT

#include "scene/3d/node_3d.h"
class Grid;

class GridObject : public Node3D {
	GDCLASS(GridObject, Node3D);

private:
	std::shared_ptr<Grid> GridPtr;
	bool ValidGrid = false;
protected:
	static void _bind_methods();
public:
	void register_grid(Grid* grid);
	GridObject();
	//Destructor, get yourself off the grid
};

#endif
