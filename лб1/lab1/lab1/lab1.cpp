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
#define STUD_COUNT 5     /* начальное количество студентов в задании 5 */
#define MAX_STUDENTS 50  /* максимальное количество студентов */
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
        printf(" 4. Студенты: добавление и поиск по подстроке\n");
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

    /* на главной диагонали (i == j) только положительные числа из [1, 10],
       остальные элементы - из [-10, 10] */
    printf("\nМатрица %dx%d (главная диагональ в скобках):\n", rows, cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (i == j) {
                a[i][j] = 1 + rand() % 10;
                printf("  [%2d]", a[i][j]);
            }
            else {
                a[i][j] = rand() % 21 - 10;
                printf("%6d", a[i][j]);
            }
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

/* Список студентов хранится между вызовами task5(), поэтому добавленные
   студенты сохраняются до конца работы программы */
struct student stud[MAX_STUDENTS] = {
    { "Иванов",   "Иван",    "ФВТ", 25001 },
    { "Петров",   "Пётр",    "ФПИ", 25002 },
    { "Сидорова", "Анна",    "ФВТ", 25003 },
    { "Кузнецов", "Иван",    "ФЭУ", 25004 },
    { "Смирнова", "Мария",   "ФПИ", 25005 }
};
int stud_count = STUD_COUNT;

void print_students(void)
{
    int i;
    printf("Список студентов (%d):\n", stud_count);
    for (i = 0; i < stud_count; i++)
        print_student(stud[i]);
}

/* Добавление нового студента в конец массива */
void add_student(void)
{
    struct student s;

    if (stud_count >= MAX_STUDENTS) {
        printf("Ошибка: список заполнен (максимум %d студентов)!\n", MAX_STUDENTS);
        return;
    }
    printf("Фамилия: ");
    scanf("%19s", s.famil);
    printf("Имя: ");
    scanf("%19s", s.name);
    printf("Факультет: ");
    scanf("%19s", s.facult);
    printf("Номер зачётки: ");
    if (scanf("%d", &s.Nomzach) != 1 || s.Nomzach <= 0) {
        printf("Ошибка: номер должен быть целым числом > 0! Студент не добавлен.\n");
        clear_input();
        return;
    }
    stud[stud_count] = s;
    stud_count++;
    printf("Студент добавлен.\n");
}

/* Поиск студентов, у которых выбранное поле содержит подстроку key */
void search_students(void)
{
    char key[STR_LEN], num[STR_LEN];
    const char* value;
    int field, i, found = 0;

    printf("Поле для поиска: 1 - фамилия, 2 - имя, 3 - факультет, 4 - номер зачётки\n");
    printf("Ваш выбор: ");
    if (scanf("%d", &field) != 1 || field < 1 || field > 4) {
        printf("Ошибка: неверный параметр!\n");
        clear_input();
        return;
    }
    printf("Введите подстроку: ");
    scanf("%19s", key);

    printf("\nРезультаты поиска по подстроке \"%s\":\n", key);
    for (i = 0; i < stud_count; i++) {
        switch (field) {
        case 1: value = stud[i].famil; break;
        case 2: value = stud[i].name; break;
        case 3: value = stud[i].facult; break;
        default:
            sprintf(num, "%d", stud[i].Nomzach);   /* номер ищется как строка */
            value = num;
        }
        if (strstr(value, key) != NULL) {
            print_student(stud[i]);
            found++;
        }
    }

    if (found == 0)
        printf("  Студенты с заданной подстрокой не найдены.\n");
    else
        printf("Найдено записей: %d\n", found);
}

/* Задание 5: добавление студентов и поиск структуры student по подстроке */
void task5(void)
{
    int choice;

    printf("--- Задание 5: студенты ---\n");
    do {
        printf("\n 1. Показать список\n 2. Добавить студента\n 3. Поиск по подстроке\n 0. Назад\n");
        printf("Ваш выбор: ");
        if (scanf("%d", &choice) != 1) {
            if (feof(stdin))
                return;
            printf("Ошибка: введите целое число!\n");
            clear_input();
            choice = -1;
            continue;
        }
        switch (choice) {
        case 1: print_students(); break;
        case 2: add_student(); break;
        case 3: search_students(); break;
        case 0: break;
        default: printf("Неверный выбор.\n");
        }
    } while (choice != 0);
}
