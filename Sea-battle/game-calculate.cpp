#include "game-calculate.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

field generete_fild(short size, number_ships number_ships)
{
	field battlefield;
	battlefield.size = size;

	for (short i = 0; i < MAX_SIZE - 1; i++) // Очистка массива
	{
		for (short j = 0; j < battlefield.size; j++)
		{
			battlefield.battlefield[i][j] = empty;
		}
	}

	short ship_lenght = 3;
	if (number_ships.ship[3] > 0)
		ship_lenght = 3;
	else if (number_ships.ship[2] > 0)
		ship_lenght = 2;
	else if (number_ships.ship[1] > 0)
		ship_lenght = 1;
	else if (number_ships.ship[0] > 0)
		ship_lenght = 0;
	float ship_count = ship_lenght;
	while (ship_lenght >= 0) // Выбор координат
	{
		bool continue_position = false;
		short i, j; // координаты
		i = rand() % battlefield.size;
		j = rand() % battlefield.size;
		if (battlefield.battlefield[i][j] != empty)
			continue;

		short orientation = rand() % 4;
		for (short number_turns = 0; number_turns < 6; number_turns++) // Выбор ориентации
		{
			if (number_turns == 4)
			{
				continue_position = true;
				break;
			}
			bool continue_orientation = false;

			// Проверка границ карты
			if (i < ship_lenght && orientation == up)
				continue;
			if (i >= (battlefield.size - ship_lenght) && orientation == down)
				continue;
			if (j < ship_lenght && orientation == left)
				continue;
			if (j >= (battlefield.size - ship_lenght) && orientation == right)
				continue;

			switch (orientation) // Сканирование
			{
			case up:
				for (short scan = 1; scan <= ship_lenght; scan++)
				{
					if (battlefield.battlefield[i - scan][j] != empty)
						continue_orientation = true;
				}
				break;
			case right:
				for (short scan = 1; scan <= ship_lenght; scan++)
				{
					if (battlefield.battlefield[i][j + scan] != empty)
						continue_orientation = true;
				}
				break;
			case down:
				for (short scan = 1; scan <= ship_lenght; scan++)
				{
					if (battlefield.battlefield[i + scan][j] != empty)
						continue_orientation = true;
				}
				break;
			case left:
				for (short scan = 1; scan <= ship_lenght; scan++)
				{
					if (battlefield.battlefield[i][j - scan] != empty)
						continue_orientation = true;
				}
				break;
			}
			if (continue_orientation)
				continue;

			// Запись позиции
			switch (orientation)
			{
			case up:
				for (short record = 0; record <= ship_lenght; record++)
				{
					battlefield.battlefield[i - record][j] = ship;
					if (i - ship_lenght != 0)
						battlefield.battlefield[i - ship_lenght - 1][j] = miss;
					if (i != battlefield.size)
						battlefield.battlefield[i + 1][j] = miss;
					if (j != 0)
						battlefield.battlefield[i - record][j - 1] = miss;
					if (j != battlefield.size)
						battlefield.battlefield[i - record][j + 1] = miss;
					if (i - ship_lenght != 0 && j != 0)
						battlefield.battlefield[i - ship_lenght - 1][j - 1] = miss;
					if (i - ship_lenght != 0 && j != battlefield.size)
						battlefield.battlefield[i - ship_lenght - 1][j + 1] = miss;
					if (i != battlefield.size && j != 0)
						battlefield.battlefield[i + 1][j - 1] = miss;
					if (i != battlefield.size && j != battlefield.size)
						battlefield.battlefield[i + 1][j + 1] = miss;
				}
				break;
			case down:
				for (short record = 0; record <= ship_lenght; record++)
				{
					battlefield.battlefield[i + record][j] = ship;
					if (i + ship_lenght != battlefield.size)
						battlefield.battlefield[i + ship_lenght + 1][j] = miss;
					if (i != 0)
						battlefield.battlefield[i - 1][j] = miss;
					if (j != 0)
						battlefield.battlefield[i + record][j - 1] = miss;
					if (j != battlefield.size)
						battlefield.battlefield[i + record][j + 1] = miss;
					if (i + ship_lenght != battlefield.size && j != 0)
						battlefield.battlefield[i + ship_lenght + 1][j - 1] = miss;
					if (i + ship_lenght != battlefield.size && j != battlefield.size)
						battlefield.battlefield[i + ship_lenght + 1][j + 1] = miss;
					if (i != 0 && j != 0)
						battlefield.battlefield[i - 1][j - 1] = miss;
					if (i != 0 && j != battlefield.size)
						battlefield.battlefield[i - 1][j + 1] = miss;
				}
				break;
			case left:
				for (short record = 0; record <= ship_lenght; record++)
				{
					battlefield.battlefield[i][j - record] = ship;
					if (j - ship_lenght != 0)
						battlefield.battlefield[i][j - ship_lenght - 1] = miss;
					if (j != battlefield.size)
						battlefield.battlefield[i][j + 1] = miss;
					if (i != 0)
						battlefield.battlefield[i - 1][j - record] = miss;
					if (i != battlefield.size)
						battlefield.battlefield[i + 1][j - record] = miss;
					if (j - ship_lenght != 0 && i != 0)
						battlefield.battlefield[i - 1][j - ship_lenght - 1] = miss;
					if (j - ship_lenght != 0 && i != battlefield.size)
						battlefield.battlefield[i + 1][j - ship_lenght - 1] = miss;
					if (j != battlefield.size && i != 0)
						battlefield.battlefield[i - 1][j + 1] = miss;
					if (j != battlefield.size && i != battlefield.size)
						battlefield.battlefield[i + 1][j + 1] = miss;
				}
				break;
			case right:
				for (short record = 0; record <= ship_lenght; record++)
				{
					battlefield.battlefield[i][j + record] = ship;
					if (j + ship_lenght != battlefield.size)
						battlefield.battlefield[i][j + ship_lenght + 1] = miss;
					if (j != 0)
						battlefield.battlefield[i][j - 1] = miss;
					if (i != 0)
						battlefield.battlefield[i - 1][j + record] = miss;
					if (i != battlefield.size)
						battlefield.battlefield[i + 1][j + record] = miss;
					if (j + ship_lenght != battlefield.size && i != 0)
						battlefield.battlefield[i - 1][j + ship_lenght + 1] = miss;
					if (j + ship_lenght != battlefield.size && i != battlefield.size)
						battlefield.battlefield[i + 1][j + ship_lenght + 1] = miss;
					if (j != 0 && i != 0)
						battlefield.battlefield[i - 1][j - 1] = miss;
					if (j != 0 && i != battlefield.size)
						battlefield.battlefield[i + 1][j - 1] = miss;
				}
				break;
			}
			break;
		}
		if (continue_position)
			continue;

		ship_count = (ship_count - (1.0 / number_ships.ship[ship_lenght])) - EPSILON; // Проверка количества кораблей, которые осталость сгенерировать
		if (ship_count < ship_lenght - 1)
			ship_lenght = ship_lenght - 1;
	}

	for (short i = 0; i < battlefield.size; i++) // Очистка массива от "мимо"
	{
		for (short j = 0; j < battlefield.size; j++)
		{
			if (battlefield.battlefield[i][j] == miss)
				battlefield.battlefield[i][j] = empty;
		}
	}
	return battlefield;
}

number_ships generete_number_ships(short size)
{
	number_ships number_ships;
	number_ships.ship[3] = (size / 5) - 1;
	number_ships.ship[2] = size / 4;
	number_ships.ship[1] = size / 3;
	number_ships.ship[0] = size / 2.5;
	return number_ships;
}

field check_shot(coordinates shot, field battlefield)
{
	switch (battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1]])
	{
	case ship:
		battlefield.shot = hit;
		battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1]] = hit;
		battlefield = check_kill(battlefield, shot);
		break;
	case hit:
		battlefield.shot = miss;
		battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1]] = hit;
		break;
	case kill:
		battlefield.shot = miss;
		battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1]] = kill;
		break;
	default:
		battlefield.shot = miss;
		battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1]] = miss;
		break;
	}
	return battlefield;
}

coordinates enemy_turn(field battlefield)
{
	coordinates shot;
	shot.coordinate[0] = rand() % battlefield.size;
	shot.coordinate[1] = rand() % battlefield.size;
	return shot;
}

field check_kill(field battlefield, coordinates shot)
{

	while (1)
	{
		if (battlefield.battlefield[shot.coordinate[0] + 1][shot.coordinate[1]] != hit && battlefield.battlefield[shot.coordinate[0] + 1][shot.coordinate[1]] != ship)
		{
			if (battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] + 1] != hit && battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] + 1] != ship)
				break;
			else
				shot.coordinate[1]++;
		}
		else
			shot.coordinate[0]++;
	}

	bool iskill = false;
	direction orintation = down;
	short lenght = 0;
	while (1)
	{
		lenght++;
		if (battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1]] != hit)
			break;
		if (battlefield.battlefield[shot.coordinate[0] - 1][shot.coordinate[1]] != hit)
		{
			if (battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] - 1] != hit)
			{
				if (battlefield.battlefield[shot.coordinate[0] - 1][shot.coordinate[1]] != ship && battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] - 1] != ship)
				{
					iskill = true;
					break;
				}
				else
					break;
			}
			else
			{
				shot.coordinate[1] = shot.coordinate[1] - 1;
				orintation = right;
			}
		}
		else
		{
			shot.coordinate[0] = shot.coordinate[0] - 1;
			orintation = down;
		}
	}

	if (!iskill)
		return battlefield;

	battlefield.shot = kill;
	if (orintation == down)
	{
		battlefield.battlefield[shot.coordinate[0] + lenght][shot.coordinate[1] + 1] = miss;
		battlefield.battlefield[shot.coordinate[0] + lenght][shot.coordinate[1]] = miss;
		if (shot.coordinate[1] != 0)
			battlefield.battlefield[shot.coordinate[0] + lenght][shot.coordinate[1] - 1] = miss;
		if (shot.coordinate[0] != 0)
		{
			battlefield.battlefield[shot.coordinate[0] - 1][shot.coordinate[1] + 1] = miss;
			battlefield.battlefield[shot.coordinate[0] - 1][shot.coordinate[1]] = miss;
			if (shot.coordinate[1] != 0)
				battlefield.battlefield[shot.coordinate[0] - 1][shot.coordinate[1] - 1] = miss;
		}
		for (short i = 0; i < lenght; i++)
		{
			battlefield.battlefield[shot.coordinate[0] + i][shot.coordinate[1]] = kill;
			if (shot.coordinate[1] != 0)
				battlefield.battlefield[shot.coordinate[0] + i][shot.coordinate[1] - 1] = miss;
			battlefield.battlefield[shot.coordinate[0] + i][shot.coordinate[1] + 1] = miss;
		}
	}
	else
	{
		battlefield.battlefield[shot.coordinate[0] + 1][shot.coordinate[1] + lenght] = miss;
		battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] + lenght] = miss;
		if (shot.coordinate[0] != 0)
			battlefield.battlefield[shot.coordinate[0] - 1][shot.coordinate[1] + lenght] = miss;
		if (shot.coordinate[1] != 0)
		{
			battlefield.battlefield[shot.coordinate[0] + 1][shot.coordinate[1] - 1] = miss;
			battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] - 1] = miss;
			if (shot.coordinate[0] != 0)
				battlefield.battlefield[shot.coordinate[0] - 1][shot.coordinate[1] - 1] = miss;
		}
		for (short i = 0; i < lenght; i++)
		{
			battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] + i] = kill;
			if (shot.coordinate[0] != 0)
				battlefield.battlefield[shot.coordinate[0] - 1][shot.coordinate[1] + i] = miss;
			battlefield.battlefield[shot.coordinate[0] + 1][shot.coordinate[1] + i] = miss;
		}
	}
	return battlefield;
}