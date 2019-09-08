all: busca_e_conta.o bib_arqs.o
	gcc $(CFLAGS) busca_e_conta.o bib_arqs.o -o busca_e_conta
busca_e_conta.o: busca_e_conta.c bib_arqs.h
	gcc $(CFLAGS) -c busca_e_conta.c 
bib_arqs.o: bib_arqs.c bib_arqs.h
	gcc $(CFLAGS) -c bib_arqs.c
clean:
	rm -f *.o
