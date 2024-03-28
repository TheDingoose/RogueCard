#include "grid.h"

#include "../Object/grid_object.h"

Grid::Grid() {
	
	SquareSize = Vector2(1,1);
}

Dictionary Grid::get_raw_grid_data() const{
	return GridData;
}

Vector2 Grid::get_square_size() const {
	return SquareSize; 
}

void Grid::set_square_size(const Vector2 &size) {
	SquareSize = size; //Update all childrens positions??
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

ObjectID Grid::get_cell_id(const Vector2i &location) {
	if (GridData.get_valid(location)) {
		return GridData[location];
	}
	return ObjectID(); //nulll
}

Vector<ObjectID> Grid::get_line_id(const Vector2i &start, const Vector2i &end, bool include_empty = false) {
	
	Vector2i Diff = end - start;
	Vector2i Step;
	int Length;

	//is a straight or diagonal line
	if ((Diff.x == 0) != (Diff.y == 0)) { //Straight line!
		Length = Diff.x + Diff.y;
		Step = Diff / abs(Length);
	} else if (Diff.x == Diff.y) { //Diagonal
		Length = abs(Diff.x);
		Step = Diff / abs(Length);
	} else { //Neither
		return Vector<ObjectID>();
	}

	Vector<ObjectID> Ret;

	//i is the cell to check, moves step by step to the end point
	for (Vector2i i = start; start != end + Step ; i += Step) {
		ObjectID o = get_cell_id(i);
		if (!o.is_null() || include_empty) {
			Ret.push_back(o);
		}
	}

	return Ret;
} //STILL GOTTA PUT THIS INTO THE BIND, REMEMBER TO ADD THE SET FOR INCLUDE EMPTY = false

Array Grid::get_circle_coords(const Vector2i &location, int radius) {
	float adj_radius = radius + 0.5;
	Dictionary Unsorted;
	Unsorted.clear();
	for (int x = location.x - radius; x <= location.x + radius; x++) {
		for (int y = location.y - radius; y <= location.y + radius; y++) { // De for loop neemt alles in een vierkant rond de cirkel, dat helpt met het verminderen van operations.
			float xDiff = x - location.x;
			float yDiff = y - location.y;
			// om sqrt te vermijden kijken we naar ^2 values.
			float dist = xDiff * xDiff + yDiff * yDiff;
			if (dist <= adj_radius * adj_radius) // De = sign is om smoothing, dit is een debatable ding.
			{
				if (xDiff == 0) // Fix edgecase with xDiff = 0
				{
					if (yDiff > 0) {
						Unsorted[dist + 0.0001f * 90] = Vector2i(x, y);
					} else {
						Unsorted[dist + 0.0001f * 270] = Vector2i(x, y);
					}
				} else if (xDiff > 0) {
					Unsorted[dist + 0.0001f * (360 + Math::rad_to_deg(atanf(yDiff / xDiff)))] = Vector2i(x, y);
				} else if (xDiff < 0) {
					Unsorted[dist + 0.0001f * (180 + Math::rad_to_deg(atanf(yDiff / xDiff)))] = Vector2i(x, y);
				}
			}
		}
	}

	//Sort keys, then set the array

	Array Keys = Unsorted.keys();

	float key;
	int i, j;
	for (i = 1; i < Keys.size(); i++) {
		key = float(Keys[i]);
		j = i - 1;
	
		// Move elements of arr[0..i-1],
		// that are greater than key,
		// to one position ahead of their
		// current position
		while (j >= 0 && float(Keys[j]) > key) {
			Keys[j + 1] = Keys[j];
			j = j - 1;
		}
		Keys[j + 1] = key;
	}

	Array Ret;
	Ret.resize(Unsorted.size());
	for (int i = 0; i < Keys.size(); i++) {
		Ret[i] = Unsorted[Keys[i]];
	}
	return Ret;
}

Array Grid::get_hollow_circle_coords(const Vector2i &location, int inner_radius, int outer_radius) {

//if inner is smaller, swap;
	if (inner_radius > outer_radius) {
		inner_radius += outer_radius;
		outer_radius = inner_radius - outer_radius;
		inner_radius = inner_radius - outer_radius;
	}
	
	Array inner = get_circle_coords(location, inner_radius);
	Array outer = get_circle_coords(location, outer_radius);

	Array Ret;
	for (int i = inner.size(); i < outer.size(); i++) {
		Ret.push_back(outer[i]);
	}


	return Ret;
}

                   

Vector<ObjectID> Grid::get_radius_id(const Vector2i &location, int radius, bool include_empty) {

	Vector<ObjectID> Ret;

	
	if (true) { //Add location itself
		ObjectID o = get_cell_id(location);
		if (!o.is_null() || include_empty) {
			Ret.push_back(o);
		}
	}

	//first 8 cells: NW, N, NE, E, SE, S, SW, W
	if (radius >= 1) {
		ObjectID o;
		o = get_cell_id(location + Vector2i(-1, 1)); //NW
		if (!o.is_null() || include_empty) {Ret.push_back(o);}
		o = get_cell_id(location + Vector2i(0, 1)); //N
		if (!o.is_null() || include_empty) {Ret.push_back(o);}
		o = get_cell_id(location + Vector2i(1, 1)); //NE
		if (!o.is_null() || include_empty) {Ret.push_back(o);}
		o = get_cell_id(location + Vector2i(1, 0)); //E
		if (!o.is_null() || include_empty) {Ret.push_back(o);}
		o = get_cell_id(location + Vector2i(1, -1)); //SE
		if (!o.is_null() || include_empty) {Ret.push_back(o);}
		o = get_cell_id(location + Vector2i(0, -1)); //S
		if (!o.is_null() || include_empty) {Ret.push_back(o);}
		o = get_cell_id(location + Vector2i(-1, -1)); //SW
		if (!o.is_null() || include_empty) {Ret.push_back(o);}
		o = get_cell_id(location + Vector2i(-1, 0)); //W
		if (!o.is_null() || include_empty) {Ret.push_back(o);}
	}

	//other radii: 3, diags, 3, diags, 3...
	for (int i = 2; i <	radius; i++) {
		ObjectID o;
		//add the 3 top ones
		o = get_cell_id(location + Vector2i(-1, i)); //NW
		if (!o.is_null() || include_empty) {Ret.push_back(o);}
		o = get_cell_id(location + Vector2i(-1, i)); //N
		if (!o.is_null() || include_empty) {Ret.push_back(o);}
		o = get_cell_id(location + Vector2i(-1, i)); //NE
		if (!o.is_null() || include_empty) {Ret.push_back(o);}

		//the diagonal
		for (int j = 1 ; j < i - 1; j++) {
			Vector2i Step(1, -1);
			//o = get_cell_id(location + Vector2i(-1, i)); //NW
			if (!o.is_null() || include_empty) {Ret.push_back(o);}
		}


	}
	//it would be better if we then step up to 5's and get the double diags, but not sure if theres a simple algorithm for it

	return Ret;
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
	ClassDB::bind_method(D_METHOD("get_cell_id", "location"), &Grid::get_cell_id);
	ClassDB::bind_method(D_METHOD("empty_cell_data", "location"), &Grid::empty_cell_data, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("force_set_cell_data", "location", "data"), &Grid::force_set_cell_data);
	ClassDB::bind_method(D_METHOD("try_set_cell_data", "location", "data"), &Grid::try_set_cell_data);
	ClassDB::bind_method(D_METHOD("get_square_size"), &Grid::get_square_size);
	ClassDB::bind_method(D_METHOD("set_square_size", "size"), &Grid::set_square_size);
	ClassDB::bind_method(D_METHOD("get_square_size_3d"), &Grid::get_square_size_3d);


	ClassDB::bind_method(D_METHOD("get_circle_coords", "location", "radius"), &Grid::get_circle_coords);
	ClassDB::bind_method(D_METHOD("get_hollow_circle_coords", "location", "inner_radius", "outer_radius"), &Grid::get_hollow_circle_coords);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "square_size"), "set_square_size", "get_square_size");
}
