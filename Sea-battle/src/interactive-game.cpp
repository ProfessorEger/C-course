#include "interactive-game.h"
#include "ansi-colors.h"
#include <stdio.h>
#include <ctype.h>
#include <time.h>

void print_battlefield(field battlefield)
{
	short size = battlefield.size;
	short symbol_battlefield[size][size]; // Замена данных на символы (пока в тестовом режиме)
	for (short i = 0; i < size; i++)
	{
		for (short j = 0; j < size; j++)
		{
			symbol_battlefield[i][j] = battlefield.battlefield[i][j];
		}
	}

	printf("  ");
	for (short i = 0; i < size; i++) // Генерация ряда букв
	{
		char coordinate_letter = 65 + i;
		printf("  %c ", coordinate_letter);
	}
	printf("\n");

	for (short i = 0; i <= size * 2; i++) // строки
	{
		for (short j = 0; j <= size * 2; j++) // столбцы
		{
			if (i == 0 && j == 0)
				printf("  ┌─");
			else if (i == 0 && j == size * 2)
				printf("─┐");
			else if (i == size * 2 && j == 0)
				printf("  └─");
			else if (i == size * 2 && j == size * 2)
				printf("─┘");
			else if (i == 0 && j % 2 == 0)
				printf("─┬─");
			else if (i == 0)
				printf("─");
			else if (i == size * 2 && j % 2 == 0)
				printf("─┴─");
			else if (i == size * 2)
				printf("─");
			else if (j == 0 && i % 2 == 0)
				printf("  ├─");
			else if (j == 0)
			{
				short coordinate_number = (i + 1) / 2; // Генерация столбца чисел
				printf("%2hd│ ", coordinate_number);
			}
			else if (j == size * 2 && i % 2 == 0)
				printf("─┤");
			else if (j == size * 2)
				printf(" │");
			if (i % 2 == 0 && i != 0 && i != size * 2)
			{
				if (j % 2 == 0 && j != 0 && j != size * 2)
					printf("─┼─");
				else if (j != 0 && j != size * 2)
					printf("─");
			}
			else if (i != 0 && i != size * 2)
			{
				if (j % 2 == 0 && j != 0 && j != size * 2)
				{
					printf(" │ ");
				}
				else if (j != 0 && j != size * 2)
				{
					switch (symbol_battlefield[(i - 1) / 2][(j - 1) / 2])
					{
					case empty:
						printf(" ");
						break;
					case ship:
						if (battlefield.visible)
							printf(TEXT_LIGHT_BLUE("◻"));
						else
							printf(" ");
						break;
					case hit:
						printf(TEXT_PUROLE("☒"));
						break;
					case kill:
						printf(TEXT_RED("◼"));
						break;
					case miss:
						printf(TEXT_GREEN("·"));
						break;
					default:
						symbol_battlefield[i][j] = '%';
						break;
					}
				}
				printf("%c", symbol_battlefield[(i - 1) / 2][(j - 1) / 2]);
			}
		}
		if (i == battlefield.size - 1)
		{
			if (battlefield.this_is_player_field)
				printf("   Ваше поле");
			else
				printf("   Поле противника");
		}
		printf("\n");
	}
}

coordinates coordinate_read(short size)
{
	coordinates coordinates;
	char letter_coordinate = '\0';
	short number_coordinate = 0;
	while (1)
	{
		int input_check = scanf("%c%hd", &letter_coordinate, &number_coordinate);
		char check_char = '\0';
		while (scanf("%c", &check_char), check_char != '\n')
		{
			if (!isblank(check_char))
				input_check = 0;
		}
		coordinates.coordinate[1] = letter_coordinate - 65; // столбец
		coordinates.coordinate[0] = number_coordinate - 1;	// строка
		if (letter_coordinate - 65 < 0 || letter_coordinate - 65 > (size - 1) || number_coordinate - 1 < 0 || number_coordinate > size)
		{
			printf("Некорректный ввод\n");
			continue;
		}
		if (input_check == 2)
			break;
		printf("Некорректный ввод\n");
	}
	return coordinates;
}

short read_size()
{
	printf("Введите размер поля (3 - 50)\n");
	short size = 0;
	while (1)
	{
		int input_check = scanf("%hd", &size);
		char check_char = '\0';
		while (scanf("%c", &check_char), check_char != '\n')
		{
			if (!isblank(check_char))
				input_check = 0;
		}
		if (size < 3 || size > 50)
		{
			printf("Некорректный ввод\n");
			continue;
		}
		if (input_check == 1)
			break;
		printf("Некорректный ввод\n");
	}
	return size;
}

void print_game(field enemy_battlefield, field player_battlefield)
{
	print_battlefield(player_battlefield);
	print_battlefield(enemy_battlefield);
}

void print_shot(short shot, bool this_is_player_field)
{
	switch (shot)
	{
	case miss:
		if (this_is_player_field)
			printf(" - Мимо!\nВаш ход...\n");
		else
			printf(" - Мимо!\nМой ход...\n");
		break;
	case hit:
		if (this_is_player_field)
		{
			printf(TEXT_BACKGROUND_PURPLE(" - Попал!"));
			printf("\nМой ход...\n");
		}
		else
		{
			printf(TEXT_BACKGROUND_BLUE(" - Попал!"));
			printf("\nВаш ход...\n");
		}
		break;
	case kill:
		if (this_is_player_field)
		{
			printf(TEXT_BACKGROUND_RED(" - Убил!"));
			printf("\nМой ход...\n");
		}
		else
		{
			printf(TEXT_BACKGROUND_GREEN(" - Убил!"));
			printf("\nВаш ход...\n");
		}
		break;

	default:
		printf(("- Удачной игры!\nВаш ход...\n"));
		break;
	}
}

void print_coordinates_shot(coordinates shot)
{
	char letter_coordinate = 65 + shot.coordinate[1];
	short number_coordinate = shot.coordinate[0] + 1;
	printf(" - %c%hd\n", letter_coordinate, number_coordinate);
}

void print_game_over(field enemy_battlefield, field player_battlefield, bool win)
{
	enemy_battlefield.visible = true;
	print_game(enemy_battlefield, player_battlefield);
	if (win)
	{
		printf(TEXT_BACKGROUND_GREEN(" - Убил!"));
		printf("\n\n");
		printf(TEXT_GREEN("ПОБЕДА!"));
		printf("\n\n");
	}
	else
	{
		printf(TEXT_BACKGROUND_RED(" - Убил!"));
		printf("\n\n");
		printf(TEXT_RED("ПОРАЖЕНИЕ"));
		printf("\n\n");
	}
}