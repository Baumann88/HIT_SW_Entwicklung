//-----------------------------------------------------------------------------
/*!
   \internal
   \file        ProDB_AppNetwork.c
   \brief       Application for network communication

   \implementation
   project
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     23.11.2017  W.Sun
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author             Description
   23.11.2017        W.Sun              file created
   \endhistory
*/
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stwtypes.h>
#include <pthread.h>
/* -- Defines ------------------------------------------------------------- */
#define ClientAdd     1
#define ClientChk     2
#define ClientDel     3

#define MAXLINE       128
#define MaxClinet     10
/* -- Module Global Variables --------------------------------------------- */
static int client_list[MaxClinet];
static pthread_t client_thread_handle_table[MaxClinet];
static char client_ip_list[MaxClinet][20];
/* -- Module Global Function Prototypes ----------------------------------- */

/* -- Implementation ------------------------------------------------------ */


//-----------------------------------------------------------------------------
/*!
   \brief   thread_client(void *ptr)

   function thread for handle client

   \created       23.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   23.11.2017        HIT W.Sun      function created
   \endhistory
*/
//-----------------------------------------------------------------------------
void thread_client(void *ptr){
    int fd_id;
    uint8 buff[128];
    int n;

    fd_id =(int *)ptr;
    while(1){
        n = recv(fd_id, buff, MAXLINE, 0);
        buff[n] = '\0';
        printf("recv msg from client: %s\n", buff);
        close(fd_id);
    }
}


//-----------------------------------------------------------------------------
/*!
   \brief   void ip_list_update(void)

   function for update the ip_list

   \created       24.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   24.11.2017        HIT W.Sun      function created
   \endhistory
*/
//-----------------------------------------------------------------------------
void ip_list_update(void){
    uint16 iEntry;
    char path[80]="/mnt/dataflash/network_log/Ip_list.txt";
    FILE *fp = NULL;

    fp = fopen(path, "a");
    if(fseek(fp,0L,SEEK_SET)==-1){
        printf("can not update ip list");
        return;
    }

    fprintf(fp, "===============================================\n");
    for(iEntry=0;iEntry<MaxClinet;iEntry++){
        if(client_list[iEntry]>0)
            fprintf(fp, "%s\n",client_ip_list[iEntry]);
    }
    fprintf(fp, "===============================================\n");
    fclose(fp);
    fp = NULL;
}

//-----------------------------------------------------------------------------
/*!
   \brief   int clientListManage(int *fd,int aktion)

   function for management of the client list

   \created       23.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   23.11.2017        HIT W.Sun      function created
   \endhistory
*/
//-----------------------------------------------------------------------------
int clientListManage(int *fd,char *client_ip,int aktion){
    int iFD;
    int tmp;

    if(aktion==ClientAdd){
        for(iFD=0;iFD<MaxClinet;iFD++){
            if(client_list[iFD]==0){
                client_list[iFD]=*fd;
                strcpy(client_ip_list[iFD],client_ip);
                return iFD;
            }
        }
        return -1;
    }
    else if(aktion==ClientChk){
        tmp=*fd;
        for(iFD=0;iFD<MaxClinet;iFD++){
            if(client_list[iFD]==tmp){
                return iFD;
            }
        }
        return -1;
    }
    else if(aktion==ClientDel){
        tmp=*fd;
        for(iFD=0;iFD<MaxClinet;iFD++){
            if(client_list[iFD]==tmp){
                client_list[iFD]=0;
                strcpy(client_ip_list[iFD],"/");
                return iFD;
            }
        }
        return -1;
    }
}

//-----------------------------------------------------------------------------
/*!
   \brief   int main(void)

   \return

   \created       12.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   23.11.2017        HIT/W.Sun      function created
   \endhistory
*/
//-----------------------------------------------------------------------------
int main(void){
    int listenfd, connfd;
    struct sockaddr_in servaddr,clientaddr;
    int adrlen;
    int pos_client_table;
    char *ip;


    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error \n");
        return 0;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(1222);

    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        printf("bind socket error \n");
        return 0;
    }

    if( listen(listenfd, MaxClinet) == -1){
        printf("listen socket error \n");
        return 0;
    }

    printf("======waiting for client's request======\n");
    while(1){
        if( (connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &adrlen)) == -1){
            printf("accept socket error \n");
            continue;
        }
        if(connfd>0){
            if(fcntl(connfd, F_SETFL, O_NONBLOCK) == -1){
                printf("can not set this socket as non block!\n");
                close(connfd);
                continue;
            }
            ip=inet_ntoa(clientaddr.sin_addr);
            if(clientListManage(&connfd,ip,ClientAdd)==-1){
                printf("connneted client list is full!\n");
                close(connfd);
                continue;
            }
            pos_client_table=clientListManage(&connfd,ip,ClientChk);
            if(pthread_create(&client_thread_handle_table[pos_client_table], NULL, (void *)&thread_client, &connfd) != 0){
                printf("create task for client failed\n");
                clientListManage(&connfd,ip,ClientDel);
                close(connfd);
                continue;
            }
            printf("connneted device is: %s\n",inet_ntoa(clientaddr.sin_addr));
            ip_list_update();
        }
    }
    close(listenfd);
}
