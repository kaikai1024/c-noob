pkt: get_pkt.o analy_pkt.o analy_pro.o  mailAnalysis.o list.o debug.h 
	gcc -W -o pkt get_pkt.o analy_pkt.o analy_pro.o mailAnalysis.o list.o 

get_pkt.o: get_pkt.c debug.h
	gcc -W -c get_pkt.c

analy_pkt.o: analy_pkt.c debug.h
	gcc -W -c analy_pkt.c 

analy_pro.o: analy_pro.c debug.h
	gcc -W -c analy_pro.c 

mailAnalusis.o: mailAnalysis.c debug.h
	gcc -W -c mailAnalysis.c

list.o: list.c debug.h
	gcc -W -c list.c


clean: get_pkt.o analy_pkt.o analy_pro.o mailAnalusis.o list.o 
	rm *.o 
