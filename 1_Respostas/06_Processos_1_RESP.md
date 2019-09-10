1. Como se utiliza o comando `ps` para:

(a) Mostrar todos os processos rodando na máquina?
R:  ps -aux

(b) Mostrar os processos de um usuário?
R: ps -af
(c) Ordenar todos os processos de acordo com o uso da CPU?

(d) Mostrar a quanto tempo cada processo está rodando?

2. De onde vem o nome `fork()`?
R:  Do ingles, é um utensilio de duas pontas.

3. Quais são as vantagens e desvantagens em utilizar:

(a) `system()`?
R: É simples e prático.
   Não necessita de várias bibliotecas, apenas de programas nativos do sistema.
   Contra: Depende bastante do sistema, e pode acontecer erro caso o sistema não tenha a aplicação especifica usada.

(b) `fork()` e `exec()`?
R:  Não necessita de recursos do sistema, e é muito menos propenso a erros.
    Contra: A geralmente necessita de mais codigo e bibliotecas.

4. É possível utilizar o `exec()` sem executar o `fork()` antes?
É sim, porém o programa sai de execução no processo.

5. Quais são as características básicas das seguintes funções:

(a) `execp()`?
R:  Executa programas que estão no current path.

(b) `execv()`?
R:  Executa o programa especificado sem precisar de argumentos adicionais.

(c) `exece()`?
R: Executa o programa especificado + 1 argumento.
(d) `execvp()`?
R: Aceita executar o programa da current path e sem mais argumentos.

(e) `execve()`?
R: Aceita executar o programa da current path + 1 argumento

(f) `execle()`?
R: Aceita um argumento adicional que é um vararg da linguagem C.
