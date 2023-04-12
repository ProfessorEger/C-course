#include "game-calculate.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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