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
if (argc!=3){printf("Paramètres incorrects ! ");return -1;}
int port=atoi(argv[1]);
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
//int conn=connect(dSClient,(struct sockaddr *) &adR,lgA);
int taillefic;
int rec=recv(dSClient,&taillefic,sizeof(int),0);
printf("taille du fichier a recevoir: %d\n",taillefic);
char msg[250];
msg[taillefic-1]='\0';
while (1){
int nbrecu=recv(dSClient,msg,taillefic,0);
if(nbrecu==0){perror("");break;}
if(nbrecu>0){
printf("Recu : %s\n",msg);
printf("Nb octets recus : %d\n",nbrecu);}
}
FILE* fp;
char path[1000]="./recu/";
strcat(path,argv[2]);
fp=fopen(path,"w");
fwrite(&msg,1,taillefic,fp);
fclose(fp);
close(dSClient);
close(dSock);
return 0;
}