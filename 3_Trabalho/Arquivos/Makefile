all: cliente_terminal_graph.o servidor_sistema.o portal_usuario.o sistema_contas.o gerencia_contas.o gpio_sysfs.o
	gcc $(CFLAGS) servidor_sistema.o gerencia_contas.o -o servidor_sistema
	gcc $(CFLAGS) cliente_terminal_graph.o gerencia_contas.o gpio_sysfs.o -o cliente_terminal_graph `pkg-config --cflags --libs gtk+-2.0`
	gcc $(CFLAGS) sistema_contas.o gerencia_contas.o -o sistema_contas
	gcc $(CFLAGS) portal_usuario.o gerencia_contas.o gpio_sysfs.o -o portal_usuario
cliente_terminal_graph.o: cliente_terminal_graph.c gerencia_contas.h
	gcc $(CFLAGS) -c cliente_terminal_graph.c `pkg-config --cflags --libs gtk+-2.0`
servidor_sistema.o: servidor_sistema.c gerencia_contas.h gpio_sysfs.h
	gcc $(CFLAGS) -c servidor_sistema.c 
portal_usuario.o: portal_usuario.c gerencia_contas.h
	gcc $(CFLAGS) -c portal_usuario.c 
sistema_contas.o: sistema_contas.c gerencia_contas.h gpio_sysfs.h
	gcc $(CFLAGS) -c sistema_contas.c 	
gerencia_contas.o: gerencia_contas.c gerencia_contas.h
	gcc $(CFLAGS) -c gerencia_contas.c
gpio_sysfs.o: gpio_sysfs.c gpio_sysfs.h
	gcc $(CFLAGS) -c gpio_sysfs.c
clean:
	rm -f *.o
uninstall:
	rm -f *.o servidor_sistema gerencia_contas servidor_sistema cliente_terminal_graph
