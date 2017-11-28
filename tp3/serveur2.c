#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char** argv){
/*if (argc!=4){
	printf("Nombre de parametres incorrects ! Utilisation : nomprog ip port message \n");
	return -1;
}*/
int port=37041;
int taillerecu=0;
int dSock=socket(PF_INET,SOCK_STREAM,0);
if (dSock<0) {printf("Erreur lors de la creation de la socket ! ");return -1;}

struct sockaddr_in adR;
adR.sin_family=AF_INET;
adR.sin_port=htons(port);
adR.sin_addr.s_addr = INADDR_ANY;
int res1=bind(dSock,(struct sockaddr *) &adR,sizeof(adR));
if (res1==-1){printf("Erreur du bind \n");return -1;}
listen(dSock,2);
struct sockaddr_in adClient;
socklen_t lgA = sizeof(struct sockaddr_in);

int dSClient=accept(dSock,(struct sockaddr *) &adClient,&lgA);
int conn=connect(dSock,(struct sockaddr *) &adR,lgA);
while (1){
char msg[2001];
msg[2000]='\0';
int nbrecu=recv(dSClient,msg,sizeof(msg),0);
printf("Recu : %s\n",msg);
taillerecu+=nbrecu;
printf("Nb octets recus : %d\n",taillerecu);
}

close(dSClient);
close(dSock);
return 0;
}