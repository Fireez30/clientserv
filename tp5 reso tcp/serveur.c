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
if (argc!=1){printf("Paramètres incorrects ! ");return -1;}
int port=3271;
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


while (1){
int dSClient=accept(dSock,(struct sockaddr *) &adClient,&lgA);
int x=fork();
if(x==0){//enfant
int taillefic;
int rec=recv(dSClient,&taillefic,sizeof(int),0);
printf("taille du fichier a recevoir: %d\n",taillefic);
int taillenom;
int tnm=recv(dSClient,&taillenom,sizeof(int),0);
printf("taille du nom du fichier a recevoir: %d\n",taillenom);
char msg[taillefic];
msg[taillefic-1]='\0';
int nbrecu=recv(dSClient,msg,taillefic,0);
if(nbrecu==0){perror("");break;}
if(nbrecu>0){
printf("Recu : %s\n",msg);
printf("Nb octets recus : %d\n",nbrecu);}
FILE* fp;
char path[260]="./recu/";
char nomfic[taillenom];
nomfic[taillenom]='\0';
int nmfic=recv(dSClient,nomfic,taillenom,0);
strcat(path,nomfic);
fp=fopen(path,"w");
fwrite(&msg,1,taillefic,fp);
fclose(fp);
close(dSClient);
}
else if (x>0) {}
else {printf("Erreur ! Trop de processus. \n");}
}
close(dSock);
return 0;
}