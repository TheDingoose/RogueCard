#ifndef GRID_PAWN
#define GRID_PAWN

#include "grid_object.h"
#include "status_effects.h"
//track damage, statusses, with overwritable functions to apply them, so that we can setup enums to stop them

enum StatusEffect {
	DUMMY = 0,
	BURNING,
	SLOWED,
	HEALING,
	DUCKIFIED
};

class GridPawn : public GridObject {
	GDCLASS(GridPawn, GridObject);

	private:

	unsigned int MaxHealth;
	int Health;
	int Armor;

	//THIS SHOULD BE SOMEHTING DIFFERENT
	HashMap<StatusEffect, int> StatusEffects;

	int Team; //Should be an enum eventually!

	protected:
		static void _bind_methods();
	public:

	GridPawn();

	void turn_start();
	void turn_end();

	void set_max_health(int amount) {MaxHealth = amount; Health = fmin(MaxHealth, Health);};
	int get_max_health() {return MaxHealth;};

	void set_health(int amount) {Health = amount;};
	int get_health() {return Health;};

	void set_armor(int amount) {Armor = amount;};
	int get_armor() {return Armor;};

	void set_team(int team) {Team = team;}
	int get_team() {return Team;}

	void change_max_health(int change);
	void change_health(int change); //optional damage type??
	void change_armor(int change);

	void set_status(HashMap<StatusEffect, int> status);
	HashMap<StatusEffect, int> get_status();

	void apply_status(StatusEffect effect, int intensity);
	void remove_status(StatusEffect effect);

	void death();

};

#endif // GRID_PAWN
