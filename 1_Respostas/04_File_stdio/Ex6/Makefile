all: cat_falsificado.o bib_arqs.o
	gcc $(CFLAGS) cat_falsificado.o bib_arqs.o -o cat_falsificado
cat_falsificado.o: cat_falsificado.c bib_arqs.h
	gcc $(CFLAGS) -c cat_falsificado.c 
bib_arqs.o: bib_arqs.c bib_arqs.h
	gcc $(CFLAGS) -c bib_arqs.c
clean:
	rm -f *.o
