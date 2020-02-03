#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include "CJSON.h"
#include <string.h>
#include <winsock2.h>
#define MAX 80
#define PORT 12345
#define SA struct sockaddr
#define CJSON_NESTING_LIMIT 1000000000
int flag=0;
int client_socket, server_socket;char*AuthToken;
	struct sockaddr_in servaddr, cli;

	int number;

void aslMenu()
{
    puts("<MENU>");
    printf("starting menu\n");
    printf("1:register\n2:log in\n");
	char *special=calloc(100,1);
	puts("<do you want to exit?  (Yes or No)>");
	gets(special);
	if(!strcmp(special,"Yes")|| !strcmp(special,"yes"))
    {
        flag=1;
        return;
    }
    printf("enter your choice:\n");


    char choice = getchar();
    char e = getchar();


	if(choice == '1')
    {
        number=1;
        return;
    }

    else if(choice == '2'){
                number=2;
                return;
                            }
    else
            {

             number =0 ;
                return;
            }
}
void registerMe()
{
    puts("<REGISTERING>\n");
    char*buffer=calloc(100,1);
	char*username=calloc(100,1);char*password=calloc(1000,1);
        puts("enter your user name:");
        gets(username);
        puts("enter your password:");
        gets(password);


        strcat(buffer,"register");
        strcat(buffer," ");
        strcat(buffer,username);
        strcat(buffer,", ");
        strcat(buffer,password);
        strcat(buffer,"\n");


char*result=malloc(strlen(buffer));
strcpy(result,buffer);
        // Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
	else
		printf("Successfully connected to the server..\n");

    char*javab=calloc(100,1);
	int i;char*kar=calloc(strlen(result),sizeof(char));
	for(i=0;i<strlen(result);i++)
    {
        *(kar+i) = *(result+i);

    }
        send(client_socket,kar,strlen(kar),0);
        recv(client_socket,javab,100,0);
        closesocket(client_socket);
      cJSON *respond = NULL;
       respond=cJSON_Parse(javab);
        cJSON *tale = NULL;
        tale=cJSON_GetObjectItemCaseSensitive(respond,"type");


     char*pal = calloc(100,1);
      if(!strcmp(tale->valuestring,"Successful"))
        {
            printf("<you are successfully added>\n");
          number=2;
          return;
        }


    else
        {
        printf("<something is wrong please check again>\n");
        number=0;
        return;
        }

}



void login()
{
    puts("<LOG IN>");
     char*buffer=calloc(100,1);
	char*username=calloc(100,1);char*password=calloc(1000,1);

        printf("hi user\nplease give me your username:\n");
        gets(username);
        printf("please give me your password:\n");
        gets(password);
        strcat(buffer,"login");
        strcat(buffer," ");
        strcat(buffer,username);
        strcat(buffer,", ");
        strcat(buffer,password);
        strcat(buffer,"\n");


char*result = malloc(strlen(buffer));
strcpy(result,buffer);
        // Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
	else
		printf("Successfully connected to the server..\n");

    char*javab=calloc(100,1);
	int i;char*kar=calloc(strlen(result),sizeof(char));
	for(i=0;i<strlen(result);i++)
    {

        *(kar+i)=*(result+i);

    }
        send(client_socket,kar,strlen(kar),0);
        recv(client_socket,javab,100,0);
        closesocket(client_socket);

        cJSON*respond = cJSON_Parse(javab);
        cJSON*tale = cJSON_GetObjectItemCaseSensitive(respond,"type");
     char*pal=calloc(100,1);
     if(!strcmp(tale->valuestring,"AuthToken"))
        {

        printf("<you are successfully entered>\n ");

    cJSON*tale2 = cJSON_GetObjectItemCaseSensitive(respond,"content");

     AuthToken=(tale2->valuestring);
number=3;
return;
        }
     else
     {
         printf("<something has gone wrong>\n");
         number=2;
         return;
     }

}


void menu_conver(char*AuthToken)
{
    printf("<CHANNEL MENU>\n");
    printf("1:create a channel\n2:join channel\n3:log out\n");
    char choice;
    printf("choose your choice:\n");
    choice=getchar();
    char e=getchar();
        if(choice=='1')
                {
                    number=11;
                    return;
                }
        if(choice=='2'){
                number=6;
                return;
        }
        if(choice == '3')
                    {
                        number = 10;
                        return;
                    }




}

void create_channel(char *AuthToken)
{
    printf("<CREATE CHANNEL>\n");
    char *buffer=calloc(100,1);
	char *channelname=calloc(100,1);

        printf("hi user\nplease give me your channel name:");
        gets(channelname);
        strcat(buffer,"create channel");
        strcat(buffer," ");
        strcat(buffer,channelname);
        strcat(buffer,", ");
        strcat(buffer,AuthToken);
        strcat(buffer,"\n");
             // Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
            printf("Socket creation failed...\n");
            exit(0);
                                }
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
	else
		printf("Successfully connected to the server..\n");
char *javab=calloc(100,1);

     send(client_socket,buffer,strlen(buffer),0);
     recv(client_socket,javab,100,0);
     closesocket(client_socket);
       cJSON*respond = cJSON_Parse(javab);
       cJSON*tale = cJSON_GetObjectItemCaseSensitive(respond,"type");
     free(buffer);free(channelname);
       if(!strcmp(tale->valuestring,"Successful"))
       {
           puts("<you made a channel successfully>\n");
            number=5;
            return;
       }
       else{
                puts("<some thing is wrong>\n");
                number=3;
                return;
            }

}


void join_channel(char *AuthToken)
{
    printf("<JOIN CHANNEL>\n");
     char *buffer=calloc(100,1);
	char *channelname=calloc(100,1);

        printf("hi user\nplease give me your channel name:");
        gets(channelname);
        strcat(buffer,"join channel");
        strcat(buffer," ");
        strcat(buffer,channelname);
        strcat(buffer,", ");
        strcat(buffer,AuthToken);
        strcat(buffer,"\n");
        createsocket();

        char *javab=calloc(100,1);

     send(client_socket,buffer,strlen(buffer),0);
     recv(client_socket,javab,100,0);
     closesocket(client_socket);
       cJSON*respond = cJSON_Parse(javab);
       cJSON*tale = cJSON_GetObjectItemCaseSensitive(respond,"type");
     free(buffer);free(channelname);

       if(!strcmp(tale->valuestring,"Successful"))
       {
               puts("<you join a channel successfully>\n");
               number=5;
               return;
       }
       else{
                puts("<some thing is wrong>\n");
                number=3;
                return;
            }


}


void talk_menu(char *AuthToken)
{
    printf("<CHANNEL MENU>\n");
    printf("1:send message\n2:referesh\n3:channel members\n4:leave channel\n");
    puts("please give your choice:");
    char choice;
    choice=getchar();
    char e=getchar();

    if(choice == '1')
        number=4;
    if(choice == '2')
            number=7;
    if(choice == '3')
            number=8;
    if(choice == '4')
            number=9;

     return;


}


void sendMessage(char *AuthToken)
{
        printf("<SEND MESSAGES>\n");
        char *buffer=calloc(1000,1);
        char *message=calloc(1000,1);

        printf("hi user\nplease give your message:");
        gets(message);
        strcat(buffer,"send");
        strcat(buffer," ");
        strcat(buffer,message);
        strcat(buffer,", ");
        strcat(buffer,AuthToken);
        strcat(buffer,"\n");
        createsocket();



        char *javab=calloc(1000,1);
        send(client_socket,buffer,strlen(buffer),0);
        recv(client_socket,javab,1000,0);
        closesocket(client_socket);
       cJSON*respond = cJSON_Parse(javab);
       cJSON*tale = cJSON_GetObjectItemCaseSensitive(respond,"type");
        if(!strcmp(tale->valuestring,"Successful"))
        {
            free(buffer);free(javab);
            free(message);
            puts("<your message is in channel now>\n");
            number=5;
            return;

        }
        else
        {
            free(buffer);free(javab);
            free(message);
            puts("<some thing is not correct>\n");
            number=5;
            return;
        }

}

void refresh(char *AuthToken)
{
    printf("<REFRESH>\n");
    char *buffer=calloc(100,1);

        strcat(buffer,"refresh");
        strcat(buffer," ");
        strcat(buffer,AuthToken);
        strcat(buffer,"\n");

            // Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		exit(0);
                                }
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
                                                                        }
	else
		printf("Successfully connected to the server..\n");

        char *javab=calloc(10000,1);

     send(client_socket,buffer,strlen(buffer),0);
     recv(client_socket,javab,10000,0);
     closesocket(client_socket);

       cJSON *tar=cJSON_Parse(javab);
       cJSON *par=cJSON_GetObjectItemCaseSensitive(tar,"type");
       if(!strcmp(par->valuestring,"List")){
                                        cJSON *kaf=cJSON_GetObjectItemCaseSensitive(tar,"content");

                                       int tare=cJSON_GetArraySize(kaf);
                                      int i;
                                      for(i=0;i<tare;i++)
                              {


                                    cJSON *finaly = cJSON_GetArrayItem(kaf,i);
                                    cJSON *man=cJSON_GetObjectItemCaseSensitive(finaly,"sender");
                                    printf("%s :",man->valuestring);
                                    cJSON *payam=cJSON_GetObjectItemCaseSensitive(finaly,"content");
                                    printf("%s\n",payam->valuestring);
                              }
                                            }

        number=5;
        return;
}



void logout(char *AuthToken)
{
        printf("<LOG OUT>\n");
       char *buffer=calloc(1000,1);
        char *channelname=calloc(1000,1);



        strcat(buffer,"logout");
        strcat(buffer," ");
        strcat(buffer,AuthToken);
        strcat(buffer,"\n");
        createsocket();

        char *javab=calloc(1000,1);

        send(client_socket,buffer,strlen(buffer),0);
        recv(client_socket,javab,1000,0);
        closesocket(client_socket);
       cJSON*respond = cJSON_Parse(javab);
       cJSON*tale = cJSON_GetObjectItemCaseSensitive(respond,"type");

        if(!strcmp(tale->valuestring,"Successful"))
        {
            free(buffer);free(javab);
            free(tale);
            puts("<good bye user>\n");
            number=0;
            return;
        }
        else
        {
            free(buffer);free(javab);

            puts("<you are with me yet>\n");
            number=3;
            return;
        }
}


void leave_channel(char *AuthToken)
{
    printf("<LEAVE  THIS CHANNEL>\n");
    char *buffer=calloc(1000,1);
	char *channelname=calloc(1000,1);
    strcat(buffer,"leave");
    strcat(buffer," ");
    strcat(buffer,AuthToken);
    strcat(buffer,"\n");
    createsocket();
    char *javab=calloc(1000,1);
     send(client_socket,buffer,strlen(buffer),0);
     recv(client_socket,javab,1000,0);
     closesocket(client_socket);
       cJSON*respond = cJSON_Parse(javab);
       cJSON*tale = cJSON_GetObjectItemCaseSensitive(respond,"type");
       if(!strcmp(tale->valuestring,"Successful"))
       {
           free(buffer);free(javab);
            free(channelname);
            puts("<Good bye>");
            number=3;
            return;
       }
       else
       {
           free(buffer);free(javab);
            free(channelname);
           puts("<unsuccessful try please try again>");
           number=3;
           return;
       }
}




void member(char *AuthToken)
{
    printf("<LIST OF MEMBERS IN THIS CHANNEL>\n");
    char *buffer=calloc(1000,1);

        strcat(buffer,"channel members");
        strcat(buffer," ");
        strcat(buffer,AuthToken);
        strcat(buffer,"\n");
        createsocket();

        char *javab=calloc(1000,1);

     send(client_socket,buffer,strlen(buffer),0);
     recv(client_socket,javab,1000,0);
     closesocket(client_socket);

       cJSON *tar=cJSON_Parse(javab);
       cJSON *par=cJSON_GetObjectItemCaseSensitive(tar,"type");
       if(!strcmp(par->valuestring,"List")){
        cJSON *kaf=cJSON_GetObjectItemCaseSensitive(tar,"content");
       int tare=cJSON_GetArraySize(kaf);
      int i;
      for(i=0;i<tare;i++)
      {


    cJSON *finaly = cJSON_GetArrayItem(kaf,i);

        printf("%s\n",finaly->valuestring);
      }
       }

     number=5;
     return;

}
void createsocket()
{
    // Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
	else
		printf("Successfully connected to the server..\n");
	return;
	}

int main()
{


	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

	// Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
                  }


	createsocket();



	// Close the socket
	closesocket(client_socket);
	printf("<Hi,welcome to my chatroom>\n");
    number = 0;
    while(true){
        if(number==0)
            aslMenu();
        if(number==1)
            registerMe();
        if(number==2)
            login();
        if(number==3)
            menu_conver(AuthToken);
        if(number==4)
            sendMessage(AuthToken);
        if(number==5)
            talk_menu(AuthToken);

        if(number==6)
            join_channel(AuthToken);
        if(number==7)
            refresh(AuthToken);
        if(number==8)
            member(AuthToken);
        if(number==9)
            leave_channel(AuthToken);
        if(number == 10)
                logout(AuthToken);
        if(number == 11)
            create_channel(AuthToken);


        if(flag==1)
            return;
    }
}




