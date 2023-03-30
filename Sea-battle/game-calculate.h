#ifndef GAME_CALCULATE_H
#define GAME_CALCULATE_H
#include "main.h"

const float EPSILON = 0.001;

typedef enum
{
	up,
	right,
	down,
	left
} direction;

field generete_fild(short size, number_ships number_ships);//Генерирует случайное поле
number_ships generete_number_ships(short size);// Генерирует количесвтво кораблей
field check_shot(coordinates shot, field battlefield);//Проверяет выстрел (Попал, убил, мимо)
coordinates enemy_turn(field battlefield);//Компьютер делает выстрел
field check_kill(field battlefield, coordinates edge); //Проверяет, уничтожен ли корабль и выводит поле

#endif