pkt: get_pkt.o analy_pkt.o analy_pro.o  mailAnalysis.o list.o debug.o 
	gcc -W -o pkt get_pkt.o analy_pkt.o analy_pro.o mailAnalysis.o list.o debug.o

get_pkt.o: get_pkt.c
	gcc -W -c get_pkt.c

analy_pkt.o: analy_pkt.c 
	gcc -W -c analy_pkt.c 

analy_pro.o: analy_pro.c 
	gcc -W -c analy_pro.c 

mailAnalusis.o: mailAnalysis.c
	gcc -W -c mailAnalysis.c

list.o: list.c
	gcc -W -c list.c

debug.o: debug.c
	gcc -W -c debug.c

clean: get_pkt.o analy_pkt.o analy_pro.o mailAnalusis.o list.o debug.o
	rm *.o 
