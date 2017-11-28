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
if (argc!=3){
	printf("Nombre de parametres incorrects ! Utilisation : nomprog ip port \n");
	return -1;
}
int dSock=socket(PF_INET,SOCK_STREAM,0);
if (dSock<0) {printf("Erreur lors de la creation de la socket ! ");return -1;}


struct sockaddr_in adR;
adR.sin_family=AF_INET;
adR.sin_port=htons(atoi(argv[2]));
int res =inet_pton(AF_INET,argv[1],&(adR.sin_addr));
if (res!=1) {printf("Erreur lors du stockage de l'adresse !");return -1;}

socklen_t lgAd=sizeof(adR);

char m[120];
m[120]='\0';
printf("message : \n");
fgets(m,120,stdin);

int conn=connect(dSock,(struct sockaddr *) &adR,lgAd);
int res2=send(dSock,m,strlen(m)+1,0);
if (res2==-1){printf("Erreur lors de l'envoi ! ");perror("perror :");return -1;}

int taillerecu;
recv(dSock,&taillerecu,sizeof(taillerecu),0);

printf("Message recu : %d\n",taillerecu);
close(dSock);
return 0;
}