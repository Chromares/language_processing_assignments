op : main.o location_counter.o op_table.o sym_table.o
	gcc main.o location_counter.o op_table.o sym_table.o -o op
main.o : main.c
	gcc -c main.c
location_counter.o : location_counter.c
	gcc -c location_counter.c
op_table.o : op_table.c
	gcc -c op_table.c
sym_table.o : sym_table.c
	gcc -c sym_table.c
