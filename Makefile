all: Photopobre

Photopobre: main.o filters.o
	gcc -o Photopobre main.o filters.o

filters.o: filters.c filters.h
	gcc -I ../01--ViBorges/ -o filters.o -c filters.c

main.o: main.c filters.h
	gcc -I ../01--ViBorges/ -o main.o -c main.c

.PHONY: clean

clean:
	rm ./Photopobre
	rm  ./*.o
