all: terminal_tranca.o sistema_contas.o gerencia_contas.o gpio_sysfs.o
	gcc $(CFLAGS) sistema_contas.o gerencia_contas.o -o sistema_contas
	gcc $(CFLAGS) terminal_tranca.o gerencia_contas.o gpio_sysfs.o -o terminal_tranca
terminal_tranca.o: terminal_tranca.c gerencia_contas.h
	gcc $(CFLAGS) -c terminal_tranca.c 
sistema_contas.o: sistema_contas.c gerencia_contas.h gpio_sysfs.h
	gcc $(CFLAGS) -c sistema_contas.c 
gerencia_contas.o: gerencia_contas.c gerencia_contas.h
	gcc $(CFLAGS) -c gerencia_contas.c
gpio_sysfs.o: gpio_sysfs.c gpio_sysfs.h
	gcc $(CFLAGS) -c gpio_sysfs.c
clean:
	rm -f *.o
uninstall:
	rm -f *.o sistema_contas.o gerencia_contas.o sistema_contas
