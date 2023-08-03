#include <stdlib.h>

#include "univ_sort.h"


// Функция для обмена местами двух элементов
// (которые лежат по адресам first_elem и second_elem, каждый элемент занимает elem_size байт):
void swap (char* first_elem, char* second_elem, size_t elem_size) {
    for (size_t i = 0; i < elem_size; i ++) {  // мы просто меняем местами в памяти каждый из elem_size байт элементов
        char temp = *(first_elem + i);  // i-ый байт первого элемента в виде числа char
        *(first_elem + i) = *(second_elem + i);
        *(second_elem + i) = temp;  // в i-ый байт второго жлемента записали число
    }
    return;
}


// Функция сортировки методом пузырька
// array - указатель (адрес) первого байта массива, который нужно отсортировать
// size - количство элементов массива, elem_size - размер (количество байтов), который занимает каждый элемент массива
// cmp - указатель на функцию сравнения элементов массива
void bubble_sort(void* array, size_t size , size_t elem_size, int (* cmp) (void* p1, void* p2 )) {
    for (size_t i = 0; i < size; i ++) {  // перебираем i-ый элемент массива
        for (size_t j = i + 1; j < size; j ++) {  // перебираем j-ый элемент - последущие элементы после i-ого
            char* arr_i = (char*) array + i * elem_size;  // указатели на эти элементы (на их первые байты) в памяти
            char* arr_j = (char*) array + j * elem_size;
            if (cmp(arr_i, arr_j) < 0)
                swap(arr_i, arr_j, elem_size);  // меняем местами, чтобы в итоге на i-ом месте оказался наименьший элемент
        }                                       // массива (не считая предыдущие i элементов, которые поставили на предыдущих шагах)
    }
    return;
}


// Сортировка слиянием
// Функция сравнения cmp возвращает число >=0, если элементы, первый и второй, в правильном порядке
//                                 и число <0, если они стоят неправильно
void merge_sort (void* array, size_t size , size_t elem_size, int (* cmp) (void* p1, void* p2 )) {
    if (size <= 1)
        return;
    
    size_t left_size = size / 2;  // вычисляем размеры половинок массива
    size_t right_size = size - left_size;
    char* left = (char*) array;  // указатели на начало каждой из половинок
    char* right = left + left_size * elem_size;

    if (size > 10) {
        merge_sort(left, left_size, elem_size, cmp);  // рекурсивно запускаем алгоритм от половинок массива
        merge_sort(right, right_size, elem_size, cmp);
    } else {
        bubble_sort(left, left_size, elem_size, cmp);  // для маленьких массиво используем сортировку пузырьком
        bubble_sort(right, right_size, elem_size, cmp);
    }


    char* temp_array = (char*) malloc(size * elem_size);  // выделяем временный массив
    char* curr = temp_array;  // указатель на текущую позицию во временном массиве

    // делаем слияние отсортированных половинок
    // (left - текущий элемент левой половинки, right - текущий элемент правой половинки)
    while (left_size > 0 && right_size > 0) {  // делаем, пока одна из половинок не кончится
        if (cmp(left, right) >= 0) {  // если left раньше right
            swap(curr, left, elem_size);  // во временный массив вставляем left
            left += elem_size;  // сдивгаем указатель
            left_size --;  // уменьшаем счётчик
        } else {  
            swap(curr, right, elem_size);  // здесь вставляем right
            right += elem_size;
            right_size --;
        }
        curr += elem_size;  // двигаем позицию
    }

    while (left_size > 0) {  // переставляем остаток левой половинки, если она осталась
        swap(curr, left, elem_size);
        left += elem_size;
        curr += elem_size;
        left_size --;
    }

    while (right_size > 0) {  // переставляем правую половинку, если она осталась
        swap(curr, right, elem_size);
        right += elem_size;
        curr += elem_size;
        right_size --;
    }

    for (size_t i = 0; i < size; i ++) {  // переставляем из временного массивк обратно в array
        swap((char*) array + i * elem_size, temp_array + i * elem_size, elem_size);
    }

    free(temp_array);  // очищаем временный массив


    return;
}
