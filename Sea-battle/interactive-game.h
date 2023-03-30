#ifndef INTERACTIVE_GAME_H
#define INTERACTIVE_GAME_H
#include "main.h"

void print_battlefield(field battlefield);
coordinates coordinate_read(short size);
short read_size();
void print_game(field enemy_battlefield, field player_battlefield);
void print_shot(short shot, bool this_is_player_field);
void print_coordinates_shot(coordinates shot);

#endif