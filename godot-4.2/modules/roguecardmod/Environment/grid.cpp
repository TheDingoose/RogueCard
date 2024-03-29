#include "grid.h"

#include "../Object/grid_object.h"

bool clockwise_compare(Vector2i center, Vector2i a, Vector2i b) {
	if (a.x - center.x >= 0 && b.x - center.x < 0)
		return true;
	if (a.x - center.x < 0 && b.x - center.x >= 0)
		return false;
	if (a.x - center.x == 0 && b.x - center.x == 0) {
		if (a.y - center.y >= 0 || b.y - center.y >= 0)
			return a.y > b.y;
		return b.y > a.y;
	}

	// compute the cross product of vectors (center -> a) x (center -> b)
	int det = (a.x - center.x) * (b.y - center.y) - (b.x - center.x) * (a.y - center.y);
	if (det < 0)
		return true;
	if (det > 0)
		return false;

	// points a and b are on the same line from the center
	// check which point is closer to the center
	int d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
	int d2 = (b.x - center.x) * (b.x - center.x) + (b.y - center.y) * (b.y - center.y);
	return d1 > d2;
}



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

Array Grid::get_line_coords(const Vector2i &start, const Vector2i &end) {

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
		return Array();
	}

	Array Ret;

	//i is the cell to check, moves step by step to the end point
	for (Vector2i i = start; start != end + Step; i += Step) {
		Ret.push_back(i);
	}

	return Ret;
}

Array Grid::get_circle_coords(const Vector2i &location, int radius) {
	float adj_radius = radius + 0.5;
	Dictionary Unsorted;
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
	Keys.sort();

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

Array Grid::get_halo_coords(const Vector2i &location, int radius) {
	float adj_radius = radius + 0.5f;
	Array Ret;

	if (radius == 0) {
		Ret.push_back(Vector2i(location.x, location.y));
		return Ret;
	}

	Ret.push_back(Vector2i(location.x, location.y + radius));
	Ret.push_back(Vector2i(location.x + radius, location.y));
	Ret.push_back(Vector2i(location.x, location.y - radius));
	Ret.push_back(Vector2i(location.x - radius, location.y));

	for (int r = 1; r <= floor(adj_radius * sqrt(0.5)); r++) {
		int d = floor(sqrt(adj_radius * adj_radius - r * r));
		if (r == d) {
			Ret.push_back(Vector2i(location.x - d, location.y + r));
			Ret.push_back(Vector2i(location.x + d, location.y + r));
			Ret.push_back(Vector2i(location.x - d, location.y - r));
			Ret.push_back(Vector2i(location.x + d, location.y - r));
		} else {	
		Ret.push_back(Vector2i(location.x - d, location.y + r));
		Ret.push_back(Vector2i(location.x + d, location.y + r));
		Ret.push_back(Vector2i(location.x - d, location.y - r));
		Ret.push_back(Vector2i(location.x + d, location.y - r));
		Ret.push_back(Vector2i(location.x + r, location.y - d));
		Ret.push_back(Vector2i(location.x + r, location.y + d));
		Ret.push_back(Vector2i(location.x - r, location.y - d));
		Ret.push_back(Vector2i(location.x - r, location.y + d));
		}
	}

	//Sort clockwise
	Vector2i key;
	int i, j;
	for (i = 1; i < Ret.size(); i++) {
		key = Vector2i(Ret[i]);
		j = i - 1;
	
		// Move elements of arr[0..i-1],
		// that are greater than key,
		// to one position ahead of their
		// current position
		while (j >= 0 && clockwise_compare(location, key, Ret[j]))
		{
			Ret[j + 1] = Ret[j];
			j = j - 1;
		}
		Ret[j + 1] = key;
	}

	return Ret;
}

Array Grid::get_square_coords(const Vector2i &location, const Vector2i &size) {
	Dictionary Unsorted;
	Vector2i Center(location + size / 2);
	for (int x = location.x; x <= location.x + size.x; x++) {
		for (int y = location.y; y <= location.y + size.y; y++) { // De for loop neemt alles in een vierkant rond de cirkel, dat helpt met het verminderen van operations.
			float xDiff = x - Center.x;
			float yDiff = y - Center.y;
			// om sqrt te vermijden kijken we naar ^2 values.
			float dist = xDiff * xDiff + yDiff * yDiff;
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
	Keys.sort();

	Array Ret;
	Ret.resize(Unsorted.size());
	for (int i = 0; i < Keys.size(); i++) {
		Ret[i] = Unsorted[Keys[i]];
	}
	return Ret;
}

//TODO: ADD FUNCTION BINDINGS AND SETUP THIS AND GET_ARRAY_DATA

Array Grid::get_array_id(const Array &locations, bool include_empty = false) {

	Array Ret;

	for (int i = 0; i < locations.size(); i++) {
		ObjectID id = get_cell_id(locations[i]); //DOES THIS WORK??
		if (include_empty || !id.is_null()) {
			Ret.push_back(id);
		}
	}
	return Ret;
}

Array Grid::get_array_data(const Array &locations, bool include_empty = false) {

	Array Ret;

	for (int i = 0; i < locations.size(); i++) {
		GridObject* obj = get_cell_data(locations[i]); //DOES THIS WORK??
		if (include_empty || obj != nullptr) {
			Ret.push_back(obj);
		}
	}
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
	ClassDB::bind_method(D_METHOD("get_halo_coords", "location", "radius"), &Grid::get_halo_coords);
	ClassDB::bind_method(D_METHOD("get_square_coords", "location", "size"), &Grid::get_square_coords);
	ClassDB::bind_method(D_METHOD("get_array_id", "array", "include_empty"), &Grid::get_array_id, DEFVAL(false));
	ClassDB::bind_method(D_METHOD("get_array_data", "array", "include_empty"), &Grid::get_array_data, DEFVAL(false));

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "square_size"), "set_square_size", "get_square_size");
}
