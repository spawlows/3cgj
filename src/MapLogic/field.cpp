#include "field.h"
#include <cassert>
#include "field_impl.h"
int Field::assigned_field[NUM_FIELD_TYPES];

void Field::EnsureFieldIdsInitialized()
{
	static bool initialized = false;
	if (initialized) {
		return;
	}
	assigned_field[WALL_HORIZONTAL] = 5;

	assigned_field[WALL_VERTICAL] = 13;
	assigned_field[WALL_CROSS] =  02;
	assigned_field[WALL_LT] = 3;
	assigned_field[WALL_RT] = 9;
	assigned_field[WALL_LB] = 1;
	assigned_field[WALL_RB] = 4; 
	assigned_field[T_LEFT] =  6;
	assigned_field[T_RIGHT] = 11;
	assigned_field[T_TOP] =  12;
	assigned_field[T_BOTTOM] =  10;
	assigned_field[FLOOR] = 7;
	assigned_field[DOOR] = 7;
	assigned_field[DOOR_VERTICAL_CLOSED] = 17;
	assigned_field[DOOR_VERTICAL_OPEN] = 16;
	assigned_field[DOOR_HORIZONTAL_CLOSED] = 14;
	assigned_field[DOOR_HORIZONTAL_OPEN] = 15;
	assigned_field[MEDKIT] = 25;
	assigned_field[DOSKEY] = 26;
	initialized = true;
}
int Field::GetTileId()
{
	EnsureFieldIdsInitialized();
	return assigned_field[GetType()];
}
bool Field::IsObstacle() {
	if (someone_is_here) {
		return true;
	}
	if (GetType()==DOOR_VERTICAL_CLOSED ||
	    GetType()==DOOR_HORIZONTAL_CLOSED)
	 	return true;
	return (type>=WALL && type <=T_BOTTOM);
}
int doskey_active=0;
int Field::GetType() {
	if (type==DOOR_VERTICAL_CLOSED && doskey_active)
		return DOOR_VERTICAL_OPEN;
	if (type==DOOR_HORIZONTAL_CLOSED && doskey_active)
		return DOOR_HORIZONTAL_OPEN;

	return type;
}

void Field::SteppedOver(Character * who)
{
	if (type==DOSKEY)
		doskey_active++;
	if (type==DOOR_VERTICAL_CLOSED)
		type=DOOR_VERTICAL_OPEN;
	if (type==DOOR_HORIZONTAL_CLOSED)
		type=DOOR_HORIZONTAL_OPEN;
	someone_is_here=who;
}

void Field::LeftField()
{
	if (type==DOSKEY)
		doskey_active--;
	someone_is_here=0;
}

Character* Field::WhoIsHere()
{
	return someone_is_here;
}