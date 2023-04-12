#ifndef GAME_CALCULATE_H
#define GAME_CALCULATE_H
#include "main.h"

field check_shot(coordinates shot, field battlefield);//Проверяет выстрел (Попал, убил, мимо)
coordinates enemy_turn(field battlefield);//Компьютер делает выстрел
field check_kill(field battlefield, coordinates edge); //Проверяет, уничтожен ли корабль и выводит поле

#endif