#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char** argv){
if (argc!=4){
	printf("Nombre de parametres incorrects ! Utilisation : nomprog ip port message \n");
	return -1;
}

int dSock=socket(PF_INET,SOCK_DGRAM,0);
if (dSock==-1) {printf("Erreur lors de la creation de la socket ! ");return -1;}
int lim=atoi(argv[3]);

struct sockaddr_in adR;
adR.sin_family=AF_INET;
adR.sin_port=htons(atoi(argv[2]));
int res =inet_pton(AF_INET,argv[1],&(adR.sin_addr));
if (res!=1) {printf("Erreur lors du stockage de l'adresse !");return -1;}

socklen_t lgAd=sizeof(adR);
int som=0;
int stock;
for (int i=1;i<=lim;i++){
stock=htons(i);
int res2=sendto(dSock,&stock,sizeof(int),0,(struct sockaddr *) &adR,lgAd);
if (res2==-1){printf("Erreur lors de l'envoi ! ");perror("perror :");return -1;}
som+=i;
printf("Somme = %d\n",som);
}

close(dSock);
return 0;
}