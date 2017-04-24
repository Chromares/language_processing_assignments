op.o :	mnt.o mdt.o para.o main.o
	gcc main mnt mdt para -o op
main.o : main.c mdt.c mnt.c para_tables.c
	gcc -c main.c -o main
mdt.o : mdt.c
	gcc -c mdt.c -o mdt
mnt.o : mnt.c
	gcc -c mnt.c -o mnt
para.o : para_tables.c
	gcc -c para_tables.c -o para
