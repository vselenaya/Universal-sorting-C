#include <assert.h> 
#include <time.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "univ_sort.h"


// Функция, проверяющая, что все элементы идут в правильном, отсортированном порядке:
// array - указатель на начало массива
// size - количество элемнтов массива, elem_size - количество байт, занимаемых каждыйм элементом
// cmp - указатель на функцию сравнения
int checker_sort (void* array, size_t size, size_t elem_size, int (* cmp) (void* p1, void* p2)) {
    char* curr = (char*) array;
    for (int i = 0; i < size - 1; i ++) {
        if (cmp(curr, curr + elem_size) < 0)  // если неправильный порядок - возвращаем 0
            return 0;
        curr += elem_size;
    }
    return 1;  // если правильный порядок - возвращаем 1
}


int cmp_int(void* p1, void* p2) {  // функция сравнения двух чисел типа int
    int* p_num_1 = (int*) p1;
    int* p_num_2 = (int*) p2;
    return (*p_num_1 - *p_num_2);  // возвращаем >=0, если первое число больше второго
}


struct product {  // заводим струткуру (свой тип данных)
    char name[256];
    long long mass;
    int cost;
};


int cmp_product(void* p1, void* p2) {  // сравненик двух элементов типа struct product
    struct product* prod_1 = (struct product*) p1;
    struct product* prod_2 = (struct product*) p2;

    return (prod_2 -> cost - prod_1 -> cost);
}


int cmp_long_double(void* p1, void* p2) {  // сравнение элементов long double
    long double* ld_1 = (long double*) p1;
    long double* ld_2 = (long double*) p2;

    if (*ld_2 >= *ld_1)
        return 1;
    else
        return -1;
}


int main() {
    long double start, end;

    srand(200);  // ядро случайных чисел
    

    // ---- ТЕСТ 1 ----
    size_t N_1 = 12;
    int array_1[] = {9, -3, 0, 22, 980, -2, -80, -6, 99, 14, 12, 1};

    bubble_sort(array_1, N_1, sizeof(int), cmp_int);
    printf("Массив array_1 отсортирован!\n");
    assert (checker_sort(array_1, N_1, sizeof(int), cmp_int) == 1);
    printf("     сортировка правильная...\n");


    // ---- ТЕСТ 2 ----
    size_t N_2 = 1000;
    int array_2[1000];
    for (int i = 0; i < 1000; i ++)
        array_2[i] = rand();
    
    bubble_sort(array_2, N_2, sizeof(int), cmp_int);
    printf("Массив array_2 отсортирован!\n");
    assert (checker_sort(array_2, N_2, sizeof(int), cmp_int) == 1);
    printf("    сортировка правильная...\n");

    
    // ---- ТЕСТ 3 ----
    size_t N_3 = 10000;
    long double array_3[10000];
    for (int i = 0; i < 10000; i ++) {
        long double numerator = rand();
        unsigned int denominator = abs(rand());
        array_3[i] = numerator / (denominator + 10);  // добавляем в знаменатель 10, чтобы он был не 0
    }
    merge_sort(array_3, N_3, sizeof(long double), cmp_long_double);
    printf("Массив array_3 отсортирован!\n");
    assert (checker_sort(array_3, N_3, sizeof(long double), cmp_long_double) == 1);
    printf("     сортировка правильная...\n");


    // ---- ТЕСТ 4 ----
    size_t N_4 = 100000;
    struct product* array_4 = (struct product*) malloc(100000 * sizeof(struct product));
    for (int i = 0; i < 100000; i ++) {
        struct product next;
        strcpy(next.name, "Product something name");  // именно так заполняется поле name, являющееся массивом!
        next.cost = rand();
        next.mass = 1423827;
        array_4[i] = next;
    }
    merge_sort(array_4, N_4, sizeof(struct product), cmp_product);
    printf("Массив array_4 отсортирован!\n");
    assert (checker_sort(array_4, N_4, sizeof(struct product), cmp_product) == 1);
    printf("     сортировка правильная...\n");
    free(array_4);
    

    // ---- ТЕСТ 5 ----
    size_t N_5 = 1e8;
    int* array_5 = (int*) malloc(N_5 * sizeof(int));  // массив большой -> память выделяем в куче с помощью malloc
    for (size_t i = 0; i < N_5; i ++)
        array_5[i] = rand();
    
    start = clock();
    merge_sort(array_5, N_5, sizeof(int), cmp_int);
    end = clock();

    printf("Массив array_5 отсортирован! Прошло: %Lf секунд\n", (end - start) / CLOCKS_PER_SEC);
    assert (checker_sort(array_5, N_5, sizeof(int), cmp_int) == 1);
    printf("     сортировка правильная...\n");
    free(array_5);


    return 0;

}

