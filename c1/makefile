test: test.o ap_manage.o debug.o
	gcc -W -o test test.o ap_manage.o debug.o

test.o: test.c ap_manage.h 
	# gcc -c test.c
	gcc -c -W test.c

ap_manage.o: ap_manage.c ap_manage.h  
	# gcc -c ap_manage.c
	gcc -c -W ap_manage.c

debug.o: debug.c debug.h
	# gcc -c debug.c
	gcc -c -W debug.c

clean: test.o ap_manage.o debug.o
	rm *.o 

