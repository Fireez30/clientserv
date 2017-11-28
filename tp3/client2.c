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
if (argc!=4){
	printf("Nombre de parametres incorrects ! Utilisation : nomprog ip port nbiteration\n");
	return -1;
}
int nbiteration=atoi(argv[3]);
int nbocenv=0;

int dSock=socket(PF_INET,SOCK_STREAM,0);
if (dSock<0) {printf("Erreur lors de la creation de la socket ! ");return -1;}


struct sockaddr_in adR;
adR.sin_family=AF_INET;
adR.sin_port=htons(atoi(argv[2]));
int res =inet_pton(AF_INET,argv[1],&(adR.sin_addr));
if (res!=1) {printf("Erreur lors du stockage de l'adresse !");return -1;}

char message1[2001];

printf("entre les deux messages : \n");
scanf("%s",message1);
message1[2000]="\0";
/*
printf("test \n");
printf("message1 : %s\n",message1);
printf("message2 : %s\n",message2);
*/
socklen_t lgAd=sizeof(adR);
int conn=connect(dSock,(struct sockaddr *) &adR,lgAd);

for (int i=0;i<nbiteration;i++){
int res2=send(dSock,message1,strlen(message1)+1,0);
if (res2==-1){printf("Erreur lors de l'envoi ! ");perror("perror :");return -1;}

nbocenv+=strlen(message1);
printf("Nb octets envoyes : %d\n",nbocenv);
}

close(dSock);
return 0;
}