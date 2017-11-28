#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
if (argc!=2){printf("Parametres incorrects ! ./nomprog nboctets");}
short int port=37541;


int dSock=socket(PF_INET,SOCK_DGRAM,0);
if (dSock==-1) {printf("Erreur lors de la creation de la socket ! ");return -1;}

struct sockaddr_in ad;
ad.sin_family=AF_INET;
ad.sin_addr.s_addr=INADDR_ANY;
ad.sin_port=htons(port);

int res=bind(dSock,(struct sockaddr*) &ad,sizeof(ad));
if (res==-1) {printf("Erreur lors du bind ! ");return -1;}
int R;
int som=0;
while (1){
recvfrom(dSock,&R,sizeof(R),0,NULL,NULL);

short int resultat=ntohs(R);

printf("Resultat = %d\n",resultat);
som+=resultat;
printf("Somme = %d\n",som);
}	
	return 0;
}