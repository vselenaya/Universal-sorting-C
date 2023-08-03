#ifndef __univ_sort__  // используем конструкцию include-гардов (guard)
#define __univ_sort__
void swap (char* first_elem, char* second_elem, size_t elem_size);  // определение (сигнатуры) функций, написанных в univ_sort.c
void bubble_sort(void* array, size_t size , size_t elem_size, int (* cmp) (void* p1, void* p2 ));
void merge_sort (void* array, size_t size , size_t elem_size, int (* cmp) (void* p1, void* p2 ));
#endif