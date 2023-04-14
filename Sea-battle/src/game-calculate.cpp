#include "game-calculate.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

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
	while (1)
	{
		for (short i = 0; i < battlefield.size; i++)
		{
			for (short j = 0; j < battlefield.size; j++)
			{
				if (battlefield.battlefield[i][j] == hit)
				{
					shot = {i, j};
					shot = finish_off_ship(shot, battlefield);
					return shot;
				}
			}
		}

		shot.coordinate[0] = rand() % battlefield.size;
		shot.coordinate[1] = rand() % battlefield.size;
		if (battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1]] == empty || battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1]] == ship)
			return shot;
	}
}

coordinates finish_off_ship(coordinates shot, field battlefield)
{
	short orientation = rand() % 4;
	for (int i = 0; i < 4;)
	{
		if (orientation == left)
			orientation = up;
		else
			orientation++;

		//printf("orientation = %hd\n", orientation);

		if (shot.coordinate[0] == 0 && orientation == up) // Проверка границы карты
			continue;
		if (shot.coordinate[0] == (battlefield.size - 1) && orientation == down)
			continue;
		if (shot.coordinate[1] == 0 && orientation == left)
			continue;
		if (shot.coordinate[1] == (battlefield.size - 1) && orientation == right)
			continue;
		i++;

		bool continue_orientation = false;
		switch (orientation) // Сканирование соседней клетки на ранение и передвижение shot
		{
		case up:
			if (battlefield.battlefield[shot.coordinate[0] - 1][shot.coordinate[1]] == hit)
			{
				shot.coordinate[0] = shot.coordinate[0] - 1;
				continue_orientation = true;
			}
			break;
		case right:
			if (battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] + 1] == hit)
			{
				shot.coordinate[1] = shot.coordinate[1] + 1;
				continue_orientation = true;
			}
			break;
		case down:
			if (battlefield.battlefield[shot.coordinate[0] + 1][shot.coordinate[1]] == hit)
			{
				shot.coordinate[0] = shot.coordinate[0] + 1;
				continue_orientation = true;
			}
			break;
		case left:
			if (battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] - 1] == hit)
			{
				shot.coordinate[1] = shot.coordinate[1] - 1;
				continue_orientation = true;
			}
			break;
		}
		if (continue_orientation == true)
			break;
	}

	for (int i = 0; i < 4;) // Сканирование соседней клетки на пустую/корабль и выстрел.
	{
		switch (orientation)
		{
		case up:
			if (battlefield.battlefield[shot.coordinate[0] - 1][shot.coordinate[1]] == ship || battlefield.battlefield[shot.coordinate[0] - 1][shot.coordinate[1]] == empty)
			{
				shot.coordinate[0] = shot.coordinate[0] - 1;
				return shot;
			}
			break;
		case right:
			if (battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] + 1] == ship || battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] + 1] == empty)
			{
				shot.coordinate[1] = shot.coordinate[1] + 1;
				return shot;
			}
			break;
		case down:
			if (battlefield.battlefield[shot.coordinate[0] + 1][shot.coordinate[1]] == ship || battlefield.battlefield[shot.coordinate[0] + 1][shot.coordinate[1]] == empty)
			{
				shot.coordinate[0] = shot.coordinate[0] + 1;
				return shot;
			}
			break;
		case left:
			if (battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] - 1] == ship || battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] - 1] == empty)
			{
				shot.coordinate[1] = shot.coordinate[1] - 1;
				return shot;
			}
			break;
		}

		if (orientation == left)
			orientation = up;
		else
			orientation++;

		if (shot.coordinate[0] == 0 && orientation == up) // Проверка границы карты
			continue;
		if (shot.coordinate[0] == (battlefield.size - 1) && orientation == down)
			continue;
		if (shot.coordinate[1] == 0 && orientation == left)
			continue;
		if (shot.coordinate[1] == (battlefield.size - 1) && orientation == right)
			continue;
		i++;
	}

	for (int i = 0; i < 2;)
	{
		if (shot.coordinate[0] == 0 && orientation == up) // Проверка границы карты
		{
			orientation = down;
			continue;
		}
		if (shot.coordinate[0] == (battlefield.size - 1) && orientation == down)
		{
			orientation = up;
			continue;
		}
		if (shot.coordinate[1] == 0 && orientation == left)
		{
			orientation = right;
			continue;
		}
		if (shot.coordinate[1] == (battlefield.size - 1) && orientation == right)
		{
			orientation = left;
			continue;
		}

		switch (orientation) // Сканирование соседней клетки на пустую/корабль и выстрел.
		{
		case up:
			if (battlefield.battlefield[shot.coordinate[0] - 1][shot.coordinate[1]] == ship || battlefield.battlefield[shot.coordinate[0] - 1][shot.coordinate[1]] == empty)
			{
				shot.coordinate[0] = shot.coordinate[0] - 1;
				return shot;
			}
			break;
		case right:
			if (battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] + 1] == ship || battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] + 1] == empty)
			{
				shot.coordinate[1] = shot.coordinate[1] + 1;
				return shot;
			}
			break;
		case down:
			if (battlefield.battlefield[shot.coordinate[0] + 1][shot.coordinate[1]] == ship || battlefield.battlefield[shot.coordinate[0] + 1][shot.coordinate[1]] == empty)
			{
				shot.coordinate[0] = shot.coordinate[0] + 1;
				return shot;
			}
			break;
		case left:
			if (battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] - 1] == ship || battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] - 1] == empty)
			{
				shot.coordinate[1] = shot.coordinate[1] - 1;
				return shot;
			}
			break;
		}

		bool continue_orientation = false;
		switch (orientation) // Сканирование соседней клетки на ранен и перемещение shot
		{
		case up:
			if (battlefield.battlefield[shot.coordinate[0] - 1][shot.coordinate[1]] == hit)
			{
				shot.coordinate[0] = shot.coordinate[0] - 1;
				continue_orientation = true;
			}
			break;
		case right:
			if (battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] + 1] == hit)
			{
				shot.coordinate[1] = shot.coordinate[1] + 1;
				continue_orientation = true;
			}
			break;
		case down:
			if (battlefield.battlefield[shot.coordinate[0] + 1][shot.coordinate[1]] == hit)
			{
				shot.coordinate[0] = shot.coordinate[0] + 1;
				continue_orientation = true;
			}
			break;
		case left:
			if (battlefield.battlefield[shot.coordinate[0]][shot.coordinate[1] - 1] == hit)
			{
				shot.coordinate[1] = shot.coordinate[1] - 1;
				continue_orientation = true;
			}
			break;
		}

		if (continue_orientation)
			continue;

		switch (orientation) // изменение направления сканирования
		{
		case up:
			orientation = down;
			break;
		case right:
			orientation = left;
			break;
		case down:
			orientation = up;
			break;
		case left:
			orientation = right;
			break;
		}
		//printf("orientation №2 = %hd\n", orientation);
		i++;
	}

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