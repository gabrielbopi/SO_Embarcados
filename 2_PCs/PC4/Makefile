all: cliente_terminal.o servidor_sistema.o gerencia_contas.o gpio_sysfs.o
	gcc $(CFLAGS) servidor_sistema.o gerencia_contas.o -o servidor_sistema
	gcc $(CFLAGS) cliente_terminal.o gerencia_contas.o gpio_sysfs.o -o cliente_terminal
cliente_terminal.o: cliente_terminal.c gerencia_contas.h
	gcc $(CFLAGS) -c cliente_terminal.c 
servidor_sistema.o: servidor_sistema.c gerencia_contas.h gpio_sysfs.h
	gcc $(CFLAGS) -c servidor_sistema.c 
gerencia_contas.o: gerencia_contas.c gerencia_contas.h
	gcc $(CFLAGS) -c gerencia_contas.c
gpio_sysfs.o: gpio_sysfs.c gpio_sysfs.h
	gcc $(CFLAGS) -c gpio_sysfs.c
clean:
	rm -f *.o
uninstall:
	rm -f *.o servidor_sistema.o gerencia_contas.o servidor_sistema
