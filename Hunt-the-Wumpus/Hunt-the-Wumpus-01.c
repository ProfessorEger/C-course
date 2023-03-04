#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int map = 0; // размер карты
    printf("Введите размер карты (рекомендуется от 3 до 20)\n");
    scanf("%d", &map);

    srand(time(NULL)); // Привязывает начальное число к времени, отчего можно получать псевдослучайные числа

    short position = 1;                        // координаты игрока
    short wumpus = (rand() % (map * map)) + 1; // координаты вампуса (должны выбираться рандомно)
    while (position == wumpus)
        wumpus = (rand() % (map * map)) + 1;
    short n = 1;                            // Строка для вывода карты
    short hole[map * map];                  // ямы
    const short chance_hole = 5;            // Коэфициент вероятности генерации ямы (чем больше, тем меньше)
    short armed = 0;                        // Вооружение игрока (0 - нет пистолета, 1 - есть)
    short gun = (rand() % (map * map)) + 1; // координаты пистолета
    while (gun == wumpus)
        gun = (rand() % (map * map)) + 1;

    for (int i = 1; i <= (map * map); i++) // генерация ям
    {

        if (i == 1 || i == wumpus)
            continue;
        else
            hole[i] = rand() % chance_hole;
    }

    short end = 0;
    while (end < 1)
    {
        if (position == wumpus) // Проверка смерти от вампуса
        {
            end = 3;
            wumpus = -(map + 1);
            break;
        }

        for (int i = 1; i <= (map * map); i++) // Проверка смерти от ямы
        {
            if (position == i && hole[i] == chance_hole - 1)
            {
                end = 2;
                break;
            }
        }
        if (end == 2)
            break;

        n = 1;
        for (int i = 1; i <= (map * map); i++) // Вывод карты
        {
            if (i == position)
                printf("  g");
            else
                printf("  .");
            if (i == (map * n) && n != map)
            {
                printf("\n");
                n = n + 1;
            }
            if (i == map * map)
                printf("\n\n");
        }

        if (position == gun) // получение пистолета
        {
            armed = armed + 1;
            printf("Вы нашли пистолет с одним патроном\n");
            gun = -map;
        }
        if (armed > 0) // наличие пистолета
            printf("У вас есть пистолет, для выстрела введите f\n");

        short smell = 0; // Чувство запаха
        if (position == wumpus - 1 && position % map != 0)
            smell = smell + 1;
        if (position == wumpus + 1 && (position - 1) % map != 0)
            smell = smell + 1;
        if (position == wumpus - map)
            smell = smell + 1;
        if (position == wumpus + map)
            smell = smell + 1;
        if (smell != 0)
            printf("Вы чувствуете запах Вампуса!\n");

        short wind = 0;
        for (int i = 1; i <= map * map; i++) // Чувство ветра
        {
            if (position == i - 1 && hole[i] == chance_hole - 1 && position % map != 0)
                wind = wind + 1;
            if (position == i + 1 && hole[i] == chance_hole - 1 && (position - 1) % map != 0)
                wind = wind + 1;
            if (position == i - map && hole[i] == chance_hole - 1)
                wind = wind + 1;
            if (position == i + map && hole[i] == chance_hole - 1)
                wind = wind + 1;
        }
        if (wind != 0)
            printf("Вы чувствуете Ветер\n");

        printf("\nДля перемещения используйте w, a, s или d и нажмте Enter\n");
        char step = 0;
        scanf(" %c", &step);
        if (step == 'w')
        {
            if (position <= map)
                printf("Вы уперлись в стену\n");
            else
                position = position - map;
        }
        if (step == 's')
        {
            if (position > map * (map - 1))
                printf("Вы уперлись в стену\n");
            else
                position = position + map;
        }
        if (step == 'a')
        {
            if ((position - 1) % map == 0)
                printf("Вы уперлись в стену\n");
            else
                position = position - 1;
        }
        if (step == 'd')
        {
            if (position % map == 0)
                printf("Вы уперлись в стену\n");
            else
                position = position + 1;
        }
        if (step == 'p')
            break;

        if (step == 'f' && armed > 0)
        {
            printf("Вы можете выстрелить в соседнюю клетку. выберете направление (w,a,s,d).\nВведите v, если передумали\n");
            char shot = 0;
            scanf(" %c", &shot);
            if (shot == 'w' && position == wumpus + map)
                end = 1;
            if (shot == 's' && position == wumpus - map)
                end = 1;
            if (shot == 'a' && position == wumpus + 1)
                end = 1;
            if (shot == 'd' && position == wumpus - 1)
                end = 1;
            if (shot == 'w' && position != wumpus + map)
            {
                printf("Вы промахнулись\n");
                armed = armed - 1;
            }
            if (shot == 's' && position != wumpus - map)
            {
                printf("Вы промахнулись\n");
                armed = armed - 1;
            }
            if (shot == 'a' && position != wumpus + 1)
            {
                printf("Вы промахнулись\n");
                armed = armed - 1;
            }
            if (shot == 'd' && position != wumpus - 1)
            {
                printf("Вы промахнулись\n");
                armed = armed - 1;
            }
            if (shot == 'v')
                continue;
        }
    }

    if (end == 1) // Окончание игры
        printf("\nВы убили Вампуса. Победа!\n");
    else if (end == 2)
        printf("\nВы упали в яму. Поражение\n");
    else if (end == 3)
        printf("\nВас съел Вампус. Поражение\n");

    return (0);
}