all: test_sort
	
clean:
	rm -rf test_sort *.o
main.o: main.c
	gcc -c -o main.o main.c
univ_sort.o: univ_sort.c
	gcc -c -o univ_sort.o univ_sort.c
test_sort: main.o univ_sort.o
	gcc -o test_sort main.o univ_sort.o