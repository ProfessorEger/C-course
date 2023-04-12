#ifndef FIELD_GENERETE_H
#define FIELD_GENERETE_H
#include "main.h"

const float EPSILON = 0.001;

field generete_fild(short size, number_ships number_ships);//Генерирует случайное поле
field clean_miss_field(field battlefield);//Отчищает поле от "мимо"
field clean_field(field battlefield);//Отчищает поле
number_ships generete_number_ships(short size);// Генерирует количесвтво кораблей

#endif