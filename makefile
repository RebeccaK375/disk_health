health_monitor: main.o directory_reader.o disk.o attributes.o program_controller.o system.o hash_table.o
	gcc -o health_monitor main.o directory_reader.o disk.o attributes.o program_controller.o system.o hash_table.o -W -Wall -std=c99 -pedantic

program_controller.o: program_controller.c program_controller.h
	gcc -c program_controller.c

main.o: main.c disk.h attributes.h program_controller.h
	gcc -c main.c

directory_reader.o: directory_reader.c
	gcc -c directory_reader.c

attributes.o: attributes.c attributes.h program_controller.h
	gcc -c attributes.c

disk.o: disk.c disk.h program_controller.h
	gcc -c disk.c

hash_table.o: hash_table.c hash_table.h
	gcc -c hash_table.c

system.o: system.c system.h disk.h program_controller.h hash_table.h
	gcc -c system.c
