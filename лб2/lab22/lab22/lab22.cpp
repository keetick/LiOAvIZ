#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

// ================= ЗАДАНИЕ 1 =================
void task1_matrix_multiplication() {
    printf("=== ЗАДАНИЕ 1: Умножение матриц ===\n");
    printf("N\t\tTime (sec)\n");
    printf("-----------------------------------\n");

    int sizes[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < num_sizes; s++) {
        int N = sizes[s];

        // Используем 1D массивы для избежания переполнения стека и ускорения работы с кэшем
        int* a = (int*)malloc(N * N * sizeof(int));
        int* b = (int*)malloc(N * N * sizeof(int));
        int* c = (int*)malloc(N * N * sizeof(int));

        if (!a || !b || !c) {
            printf("%d\t\tMemory allocation failed\n", N);
            free(a); free(b); free(c);
            continue;
        }

        // Заполнение матриц случайными числами
        for (int i = 0; i < N * N; i++) {
            a[i] = rand() % 100 + 1;
            b[i] = rand() % 100 + 1;
        }

        clock_t start = clock();

        // Умножение матриц
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int elem_c = 0;
                for (int r = 0; r < N; r++) {
                    elem_c += a[i * N + r] * b[r * N + j];
                }
                c[i * N + j] = elem_c;
            }
        }

        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%d\t\t%.4f\n", N, time_spent);

        free(a);
        free(b);
        free(c);
    }
    printf("\n");
}

// ================= ЗАДАНИЕ 2 =================

// Реализация сортировки Шелла
void shell(int* items, int count) {
    int i, j, gap, k;
    int x, a[5];
    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;
    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (j >= 0) && (x < items[j]); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

// Реализация быстрой сортировки
void qs(int* items, int left, int right) {
    // Базовый случай: если массив из 0 или 1 элемента, он уже отсортирован
    if (left >= right) return;

    int i, j;
    int x, y;
    i = left; j = right;
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;
        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

// Функция сравнения для стандартной qsort
int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Генерация массивов данных
void generate_array(int* arr, int n, int type) {
    for (int i = 0; i < n; i++) {
        if (type == 0) arr[i] = rand();             // Случайный набор
        else if (type == 1) arr[i] = i;             // Возрастающая
        else if (type == 2) arr[i] = n - i;         // Убывающая
        else if (type == 3) {                       // Возрастание -> Убывание
            if (i < n / 2) arr[i] = i;
            else arr[i] = n - i;
        }
    }
}

void task2_sorting() {
    printf("=== ЗАДАНИЕ 2: Алгоритмы сортировки ===\n");
    int N = 50000;

    int* original = (int*)malloc(N * sizeof(int));
    int* test_arr = (int*)malloc(N * sizeof(int));

    const char* types[] = { "Random (Случайный)", "Ascending (Возр.)", "Descending (Убыв.)", "Asc-Desc (Возр->Убыв)" };

    for (int type = 0; type < 4; type++) {
        printf("\n--- Набор данных: %s (N=%d) ---\n", types[type], N);
        generate_array(original, N, type);

        // 1. Сортировка Шелла
        memcpy(test_arr, original, N * sizeof(int));
        clock_t start = clock();
        shell(test_arr, N);
        clock_t end = clock();
        printf("Shell Sort:   \t%.4f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        // 2. Быстрая сортировка
        memcpy(test_arr, original, N * sizeof(int));
        start = clock();
        qs(test_arr, 0, N - 1);
        end = clock();
        printf("Quick Sort:   \t%.4f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        // 3. Стандартная qsort
        memcpy(test_arr, original, N * sizeof(int));
        start = clock();
        qsort(test_arr, N, sizeof(int), compare_ints);
        end = clock();
        printf("Std qsort:    \t%.4f sec\n", (double)(end - start) / CLOCKS_PER_SEC);
    }

    free(original);
    free(test_arr);
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Russian");

    srand(time(NULL));

    // Отключение буферизации ввода-вывода
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    task1_matrix_multiplication();
    task2_sorting();

    return 0;
}