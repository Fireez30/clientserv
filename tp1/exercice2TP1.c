#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc,char** argv){
	struct addrinfo* res;
	while (1){//permet de taper plusieurs nom et de quitter
	printf("Entrez le nom : (tapez quit pour quitter)\n");
	char c[256];
	scanf("%s",c);
	if (!strcmp(c,"quit")){return 0;}//test pour quitter
	int f=getaddrinfo(c,NULL,NULL,&res);//recuperation des infos dans la struc res
	if (f!=0) {
		printf("Error");
	}
	else {

		switch (res->ai_family){//test sur le type lip (4 ou 6)
			case AF_INET:
			printf("IPV4 :\n");
			struct addrinfo* tmp = res;
		/*	switch (tmp->ai_flags){ //recuperation du nom officiel
				case AI_CANONNAME:
					printf("nom officiel de l'hote : %s\n",tmp->ai_canonname);
				break;
				default:
				break;
			}*/
			struct sockaddr_in *sin1 = (struct sockaddr_in *) tmp->ai_addr;
			char *ip=inet_ntoa(sin1->sin_addr);//recuperation de l'ip 
    		printf("Adresse ip = %s\n",ip);
    		char host[NI_MAXHOST];
			getnameinfo(sin1,INET_ADDRSTRLEN,host,sizeof(host),NULL,0,NULL);//recuperation du nom de l'hote v2
			printf("Nom de l'hote = %s\n",host);
			tmp=tmp->ai_next;
			while (tmp->ai_next != NULL){//parcours des alias de l'hote
			struct sockaddr_in *sin = (struct sockaddr_in *) tmp->ai_addr;
			char *ip=inet_ntoa(sin->sin_addr);//recuperation de l'ip 
    		printf("Adresse ip = %s\n",ip);
    		char host[NI_MAXHOST];
			getnameinfo(sin,INET_ADDRSTRLEN,host,sizeof(host),NULL,0,NULL);//recuperation du nom de l'hote v2
			printf("Nom de l'hote = %s\n",host);
			tmp=tmp->ai_next;
		}
    		break;
			case AF_INET6://pareil qu'avant mais dans le cas d'une ipv6
			printf("IPV6 :\n");
			struct sockaddr_in6 *sin2 = (struct sockaddr_in6 *) res->ai_addr;
			char dest[INET6_ADDRSTRLEN];
			inet_ntop(res->ai_family,&(sin2->sin6_addr),dest,INET6_ADDRSTRLEN);
    		printf("Adresse ip = %s\n",dest);
    		char host2[NI_MAXHOST];
			getnameinfo(sin2,INET6_ADDRSTRLEN,host2,sizeof(host2),NULL,0,NULL);
			printf("Nom de l'hote = %s\n",host2);
			break;
			default:
			printf("Comment êtes vous arrivés la ?\n");
			break;

		}


	}
}
		freeaddrinfo(res);//rend la memoire utilisée par res
	return 0;
}