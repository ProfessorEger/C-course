#include "main.h"
#include "interactive-game.h"
#include "game-calculate.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
	short size = read_size();

	srand(time(NULL)); // Генерация
	number_ships number_ships = generete_number_ships(size);
	field enemy_battlefield;
	enemy_battlefield = generete_fild(size, number_ships);
	enemy_battlefield.this_is_player_field = false;
	enemy_battlefield.visible = false;
	field player_battlefield;
	player_battlefield = generete_fild(size, number_ships);
	player_battlefield.this_is_player_field = true;
	player_battlefield.visible = true;

	enemy_battlefield.shot = -1;
	bool enemy_miss = false;
	while (1)
	{
		coordinates player_shot; // Ход игрока
		while (1)
		{
			if (!enemy_miss)
			{
				print_game(enemy_battlefield, player_battlefield); // Выводит поле
				if (enemy_battlefield.shot != miss)
					print_shot(enemy_battlefield.shot, enemy_battlefield.this_is_player_field);
			}
			player_shot = coordinate_read(size);
			enemy_battlefield = check_shot(player_shot, enemy_battlefield);
			if (enemy_battlefield.shot == miss)
			{
				print_shot(enemy_battlefield.shot, enemy_battlefield.this_is_player_field);
				break;
			}
		}

		coordinates enemy_shot;
		while (1)
		{
			enemy_shot = enemy_turn(player_battlefield);
			print_coordinates_shot(enemy_shot);
			player_battlefield = check_shot(enemy_shot, player_battlefield);
			print_game(enemy_battlefield, player_battlefield);

			if (player_battlefield.shot != miss)
				print_shot(player_battlefield.shot, player_battlefield.this_is_player_field);

			if (player_battlefield.shot == miss)
			{
				print_shot(player_battlefield.shot, player_battlefield.this_is_player_field);
				enemy_miss = true;
				break;
			}
		}
	}
	return (0);
}