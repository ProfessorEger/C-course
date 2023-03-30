#ifndef MAIN_H
#define MAIN_H

const short MAX_SIZE = 52;

typedef enum
{
	empty, // 0 - пусто
	ship,  // 1 - корабль
	hit,   // 2 - попал
	kill,  // 3 - убил
	miss   // 4 - промах
} cell;

typedef struct field
{
	short size = 0;
	short battlefield[MAX_SIZE][MAX_SIZE];
	bool visible;
	bool this_is_player_field;
	short shot = empty;
} field;

typedef struct number_ships
{
	short ship[4];
} number_ships;

typedef struct coordinates
{
	short coordinate[2];
} coordinates;

#endif