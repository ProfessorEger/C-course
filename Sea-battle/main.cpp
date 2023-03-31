#include "main.h"
#include "interactive-game.h"
#include "game-calculate.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

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

	short total_ships = number_ships.ship[0] + number_ships.ship[1] + number_ships.ship[2] + number_ships.ship[3];
	short player_kills = 0;
	short enemy_kills = 0;
	enemy_battlefield.shot = -1;
	bool enemy_miss = false;
	bool win = false;
	while (1)
	{
		coordinates player_shot; // Ход игрока
		while (1)
		{
			if (!enemy_miss)
			{
				if (enemy_battlefield.shot == kill)
				{
					player_kills++;
					if (player_kills == total_ships)
						break;
				}
				usleep(0.9 * SECOND);
				print_game(enemy_battlefield, player_battlefield); // Выводит поле
				if (enemy_battlefield.shot != miss)
				{
					usleep(0.9 * SECOND);
					print_shot(enemy_battlefield.shot, enemy_battlefield.this_is_player_field);
				}
			}
			enemy_miss = false;
			player_shot = coordinate_read(size);
			enemy_battlefield = check_shot(player_shot, enemy_battlefield);
			if (enemy_battlefield.shot == miss)
			{
				usleep(0.9 * SECOND);
				print_shot(enemy_battlefield.shot, enemy_battlefield.this_is_player_field);
				break;
			}
		}

		if (player_kills == total_ships)
		{
			usleep(0.9 * SECOND);
			win = true;
			print_game_over(enemy_battlefield, player_battlefield, win);
			break;
		}

		coordinates enemy_shot;
		while (1)
		{
			enemy_shot = enemy_turn(player_battlefield);

			print_coordinates_shot(enemy_shot);
			player_battlefield = check_shot(enemy_shot, player_battlefield);
			usleep(1.3 * SECOND);
			print_game(enemy_battlefield, player_battlefield);
			usleep(0.9 * SECOND);
			if (enemy_battlefield.shot == kill)
			{
				enemy_kills++;
				if (enemy_kills == total_ships)
					break;
			}
			if (player_battlefield.shot != miss)
				print_shot(player_battlefield.shot, player_battlefield.this_is_player_field);

			if (player_battlefield.shot == miss)
			{
				print_shot(player_battlefield.shot, player_battlefield.this_is_player_field);
				enemy_miss = true;
				usleep(0.9 * SECOND);
				break;
			}
		}

		if (enemy_kills == total_ships)
		{
			usleep(0.9 * SECOND);
			win = false;
			print_game_over(enemy_battlefield, player_battlefield, win);
			break;
		}
	}
	return (0);
}