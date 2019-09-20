1. Especifique algumas portas importantes pré-definidas para o protocolo TCP/IP.
R:	20 e 21: FTP
	22: SSh
	23: Telnet
	25: SMTP
	53: DNS
	80: HTTP
	110: POP3
	143: IMAP
	161: SNMP
	443: HTTPS

2. Com relação a endereços IP, responda:

(a) Qual é a diferença entre endereços IP externos e locais?
R:	Com o ip externo, sua máquina é enxergada pela rede mundial de computadores (network). Com o local ela é vista pelo roteador na rede interna (host).

(b) Como endereços IP externos são definidos? Quem os define?
R:	Com 4 bytes (IPv4) usa-se os primeiros, onde a quantidade é especificada a direita. A operadora de telefonia os define.

(c) Como endereços IP locais são definidos? Quem os define?
R:	Pega-se o restante dos bytes supracitados. O roteador os define.

(d) O que é o DNS? Para que ele serve?
R: É um servidor que associa a url pretendida com o seu respectivo endereço IP.

3. Com relação à pilha de protocolos TCP/IP, responda:

(a) O que são suas camadas? Para que servem?
R:	São o nível de abstração do processo de comunicação cliente-servidor. Servem para facilitar a implentação dos sistemas e modularizar a estrutura da rede.

(b) Quais são as camadas existentes? Para que servem?
R:	Camadas:
	Aplicação - Representa o mais alto nível, e é a que os programas utilizam.
	Transporte - onde há a troca de informação entre Hosts.
	Internet - onde há a troca de informação na rede mundial de computadores.
	Enlace - a vista da comunicação entre dispositivos físicos.
		
(c) Quais camadas são utilizadas pela biblioteca de sockets?
R:	Podem ser a de Transporte, Internet ou Enlace.

(d) As portas usadas por servidores na função bind() se referem a qual camada?
R:	A camada de Transporte.

(e) Os endereços usados por clientes na função connect() se referem a qual camada?
R:	À camada de Internet.

4. Qual é a diferença entre os métodos `GET` e `POST` no protocolo HTTP?
