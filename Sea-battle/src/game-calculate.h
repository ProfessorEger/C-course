#ifndef GAME_CALCULATE_H
#define GAME_CALCULATE_H
#include "main.h"

field check_shot(coordinates shot, field battlefield);//Проверяет выстрел (Попал, убил, мимо)
coordinates enemy_turn(field battlefield);//Компьютер делает выстрел
coordinates finish_off_ship(coordinates shot, field battlefield);//Делает выстрел по раненому кораблю
field check_kill(field battlefield, coordinates edge); //Проверяет, уничтожен ли корабль и выводит поле

#endif