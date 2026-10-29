#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

#define ARR_SIZE 15      /* размер массива для заданий 1 и 2 */
#define RAND_MIN -50     /* диапазон случайных чисел */
#define RAND_MAX_VAL 50
#define STUD_COUNT 5     /* количество студентов в задании 5 */
#define STR_LEN 20

struct student {
    char famil[STR_LEN];
    char name[STR_LEN];
    char facult[STR_LEN];
    int Nomzach;
};

void task1(void);
void task3(void);
void task4(void);
void task5(void);
void clear_input(void);
void print_student(struct student s);

int main(void)
{
    int choice;

    SetConsoleCP(1251);         /* кодировка ввода и вывода консоли */
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    srand((unsigned int)time(NULL));

    do {
        printf("\n========== ЛАБОРАТОРНАЯ РАБОТА №1 ==========\n");
        printf(" 1. Разница между max и min случайного массива\n");
        printf(" 2. Массив произвольного размера\n");
        printf(" 3. Суммы по строкам и столбцам 2D массива\n");
        printf(" 4. Поиск структуры student\n");
        printf(" 0. Выход\n");
        printf("============================================\n");
        printf("Выберите пункт меню: ");

        if (scanf("%d", &choice) != 1) {
            if (feof(stdin))     /* конец ввода - выходим */
                break;
            printf("Ошибка: введите целое число!\n");
            clear_input();
            choice = -1;
            continue;
        }
        printf("\n");

        switch (choice) {
        case 1: task1(); break;
        case 2: task3(); break;
        case 3: task4(); break;
        case 4: task5(); break;
        case 0: printf("Завершение работы программы.\n"); break;
        default: printf("Неверный выбор. Введите число от 0 до 4.\n");
        }
    } while (choice != 0);

    return 0;
}

/* Очистка буфера ввода после некорректного ввода */
void clear_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Задания 1, 2: массив случайных чисел и разница между max и min */
void task1(void)
{
    int a[ARR_SIZE];
    int i, min, max;

    printf("--- Задания 1, 2: разница между max и min ---\n");
    printf("Массив случайных чисел из [%d, %d]:\n", RAND_MIN, RAND_MAX_VAL);
    for (i = 0; i < ARR_SIZE; i++) {
        a[i] = RAND_MIN + rand() % (RAND_MAX_VAL - RAND_MIN + 1);
        printf("%d ", a[i]);
    }

    min = a[0];
    max = a[0];
    for (i = 1; i < ARR_SIZE; i++) {
        if (a[i] < min) min = a[i];
        if (a[i] > max) max = a[i];
    }

    printf("\nМинимальный элемент:  %d\n", min);
    printf("Максимальный элемент: %d\n", max);
    printf("Разница max - min:    %d\n", max - min);
}

/* Задание 3: динамический массив, размер вводится с клавиатуры */
void task3(void)
{
    int* a;
    int n, i;

    printf("--- Задание 3: массив произвольного размера ---\n");
    printf("Введите размер массива: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Ошибка: размер должен быть целым числом > 0!\n");
        clear_input();
        return;
    }

    a = (int*)malloc(n * sizeof(int));
    if (a == NULL) {
        printf("Ошибка: не удалось выделить память!\n");
        return;
    }

    for (i = 0; i < n; i++)
        a[i] = rand() % 100;

    printf("Создан массив из %d элементов (%d байт):\n", n, (int)(n * sizeof(int)));
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    free(a);
    printf("Память освобождена.\n");
}

/* Задание 4: суммы значений в каждой строке и каждом столбце 2D массива */
void task4(void)
{
    int** a;
    int rows, cols, i, j, sum;

    printf("--- Задание 4: суммы в двумерном массиве ---\n");
    printf("Введите количество строк и столбцов: ");
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
        printf("Ошибка: некорректные размеры!\n");
        clear_input();
        return;
    }

    a = (int**)malloc(rows * sizeof(int*));
    if (a == NULL) {
        printf("Ошибка выделения памяти!\n");
        return;
    }
    for (i = 0; i < rows; i++) {
        a[i] = (int*)malloc(cols * sizeof(int));
        if (a[i] == NULL) {
            printf("Ошибка выделения памяти!\n");
            for (j = 0; j < i; j++) free(a[j]);
            free(a);
            return;
        }
    }

    printf("\nМатрица %dx%d:\n", rows, cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            a[i][j] = rand() % 21 - 10;
            printf("%5d", a[i][j]);
        }
        printf("\n");
    }

    printf("\nСуммы по строкам:\n");
    for (i = 0; i < rows; i++) {
        sum = 0;
        for (j = 0; j < cols; j++)
            sum += a[i][j];
        printf("  Строка %d: %d\n", i + 1, sum);
    }

    printf("Суммы по столбцам:\n");
    for (j = 0; j < cols; j++) {
        sum = 0;
        for (i = 0; i < rows; i++)
            sum += a[i][j];
        printf("  Столбец %d: %d\n", j + 1, sum);
    }

    for (i = 0; i < rows; i++)
        free(a[i]);
    free(a);
}

void print_student(struct student s)
{
    printf("  %-10s %-10s %-10s %d\n", s.famil, s.name, s.facult, s.Nomzach);
}

/* Задание 5: поиск структуры student по заданному параметру */
void task5(void)
{
    struct student stud[STUD_COUNT] = {
        { "Иванов",   "Иван",    "ФВТ", 25001 },
        { "Петров",   "Пётр",    "ФПИ", 25002 },
        { "Сидорова", "Анна",    "ФВТ", 25003 },
        { "Кузнецов", "Иван",    "ФЭУ", 25004 },
        { "Смирнова", "Мария",   "ФПИ", 25005 }
    };
    char key[STR_LEN];
    int field, num, i, found = 0, match;

    printf("--- Задание 5: поиск студента ---\n");
    printf("Список студентов:\n");
    for (i = 0; i < STUD_COUNT; i++)
        print_student(stud[i]);

    printf("\nПараметр поиска: 1 - фамилия, 2 - имя, 3 - факультет, 4 - номер зачётки\n");
    printf("Ваш выбор: ");
    if (scanf("%d", &field) != 1 || field < 1 || field > 4) {
        printf("Ошибка: неверный параметр!\n");
        clear_input();
        return;
    }

    printf("Введите значение: ");
    if (field == 4) {
        if (scanf("%d", &num) != 1) {
            printf("Ошибка: номер должен быть числом!\n");
            clear_input();
            return;
        }
    }
    else {
        scanf("%19s", key);
    }

    printf("\nРезультаты поиска:\n");
    for (i = 0; i < STUD_COUNT; i++) {
        switch (field) {
        case 1: match = strcmp(stud[i].famil, key) == 0; break;
        case 2: match = strcmp(stud[i].name, key) == 0; break;
        case 3: match = strcmp(stud[i].facult, key) == 0; break;
        default: match = stud[i].Nomzach == num;
        }
        if (match) {
            print_student(stud[i]);
            found++;
        }
    }

    if (found == 0)
        printf("  Студент с заданными параметрами не найден.\n");
    else
        printf("Найдено записей: %d\n", found);
}
