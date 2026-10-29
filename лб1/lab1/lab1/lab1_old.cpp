#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

// Константы для удобства изменения размеров
#define MAX_STUDENTS 3
#define MAX_STR_LEN 20

struct student {
    char famil[MAX_STR_LEN];
    char name[MAX_STR_LEN];
    char facult[MAX_STR_LEN];
    int Nomzach;
};

// --- ПРОТОТИПЫ ФУНКЦИЙ ЗАДАНИЙ ---
void task1(void);
void task2(void);
void task3(void);
void task4(void);

int main(void) {

    setlocale(LC_ALL, "rus");

    srand((unsigned int)time(NULL));

    int choice;

    do {
        printf("        ЛАБОРАТОРНАЯ РАБОТА №1          \n");
        printf(" 1. Разница между макс. и мин. элементами массива\n");
        printf(" 2. Создание динамического массива (ввод размера)\n");
        printf(" 3. Сумма элементов строк и столбцов 2D массива\n");
        printf(" 4. Поиск структуры student по фамилии\n");
        printf(" 0. Выход из программы\n");
        printf("----------------------------------------\n");
        printf("Выберите пункт меню (0-4): ");

        // Проверка корректности ввода числа
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка: введите целое число!\n");
            // Очистка буфера ввода от некорректных символов
            while (getchar() != '\n');
            continue;
        }

        printf("\n");

        switch (choice) {
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        case 4:
            task4();
            break;
        case 0:
            printf("Завершение работы программы. До свидания!\n");
            break;
        default:
            printf("Неверный выбор. Пожалуйста, введите число от 0 до 5.\n");
        }

    } while (choice != 0);

    return 0;
}


void task1(void) {
    printf("--- Задание 1, 2: Разница max и min ---\n");
    int a[20];

    printf("Сгенерированный массив (от -20 до 40):\n");
    for (int i = 0; i < 20; i++) {
        a[i] = -20 + rand() % 61;
        printf("%d ", a[i]);
    }

    int min = a[0];
    int max = a[0];

    for (int i = 1; i < 20; i++) {
        if (a[i] < min) min = a[i];
        if (a[i] > max) max = a[i];
    }

    printf("\nМинимальный элемент: %d\n", min);
    printf("Максимальный элемент: %d\n", max);
    printf("Разница: %d\n", max - min);
}


void task2(void) {
    printf("--- Задание 3: Динамический массив ---\n");
    int* a;
    int n;

    printf("Введите размер массива (целое число > 0): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Ошибка: некорректный размер массива!\n");
        return;
    }

    // Выделение памяти
    a = (int*)malloc(n * sizeof(int));
    if (a == NULL) {
        printf("Ошибка: не удалось выделить память!\n");
        return;
    }

    printf("Созданный массив: ");
    for (int i = 0; i < n; i++) {
        a[i] = (i + 1);
        printf("%d ", a[i]);
    }
    printf("\n");

    free(a);
    printf("Память успешно освобождена.\n");
}


void task3(void) {
    printf("--- Задание 4: Суммы в двумерном массиве ---\n");

    int rows, cols;

    printf("Введите количество строк: ");
    if (scanf("%d", &rows) != 1 || rows <= 0) {
        printf("Ошибка: некорректное количество строк!\n");
        return;
    }

    printf("Введите количество столбцов: ");
    if (scanf("%d", &cols) != 1 || cols <= 0) {
        printf("Ошибка: некорректное количество столбцов!\n");
        return;
    }

    // Динамическое выделение памяти для 2D массива
    int** a = (int**)malloc(rows * sizeof(int*));
    if (a == NULL) {
        printf("Ошибка выделения памяти!\n");
        return;
    }

    for (int i = 0; i < rows; i++) {
        a[i] = (int*)malloc(cols * sizeof(int));
        if (a[i] == NULL) {
            printf("Ошибка выделения памяти!\n");
            // Освобождаем уже выделенную память
            for (int j = 0; j < i; j++) free(a[j]);
            free(a);
            return;
        }
    }

    printf("\nСгенерированный массив:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            a[i][j] = 1 + rand() % 50;
            printf("%4d ", a[i][j]);
        }
        printf("\n");
    }

    printf("\nСумма элементов по строкам:\n");
    for (int i = 0; i < rows; i++) {
        int sum = 0;
        for (int j = 0; j < cols; j++) {
            sum += a[i][j];
        }
        printf("  Строка %d: сумма = %d\n", i + 1, sum);
    }

    printf("Сумма элементов по столбцам:\n");
    for (int j = 0; j < cols; j++) {
        int sum = 0;
        for (int i = 0; i < rows; i++) {
            sum += a[i][j];
        }
        printf("  Столбец %d: сумма = %d\n", j + 1, sum);
    }

    for (int i = 0; i < rows; i++) {
        free(a[i]);
    }
    free(a);

    printf("\nПамять успешно освобождена.\n");
}


void task4(void) {
    printf("--- Задание 5: Поиск студента ---\n");

    struct student stud[MAX_STUDENTS] = {
    {"Ivanov", "Ivan", "IT", 12345},
    {"Petrov", "Petr", "Economics", 12346},
    {"Sidorov", "Sidor", "Law", 12347},
    };

    char search_famil[MAX_STR_LEN];
    int found = 0;

    printf("Доступные фамилии для теста: Ivanov, Petrov, Sidorov\n");
    printf("Введите фамилию студента для поиска: ");

    scanf("%19s", search_famil);

    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (strcmp(stud[i].famil, search_famil) == 0) {
            printf("\n>>> Студент найден! <<<\n");
            printf("Фамилия: %s\n", stud[i].famil);
            printf("Имя: %s\n", stud[i].name);
            printf("Факультет: %s\n", stud[i].facult);
            printf("Номер зачетки: %d\n", stud[i].Nomzach);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Студент с фамилией '%s' не найден.\n", search_famil);
    }
}