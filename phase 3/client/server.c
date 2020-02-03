#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#define MAX 80
#define PORT 12345
#define SA struct sockaddr
#include "cJSON.h"

// Function designed for chat between client and server.
void chat(int client_socket)
{
    char *result=calloc(1000,sizeof(char));

    char buffer[MAX];
    int n;
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));

        // Read the message from client and copy it to buffer
        recv(client_socket, buffer, sizeof(buffer), 0);
        char *strings1=calloc(1000,1000);
        sscanf(buffer,"%s",strings1);int fault=0;
        if(strcmp(strings1,"register") == 0)
        {

            char *name=calloc(1000,1000);
            char *password=calloc(1000,1000);
            sscanf(buffer,"%*s%s",name);
            sscanf(buffer,"%*s%*s%s",password);
            printf("%s : %s %s\n",strings1,name ,password);
            strcat(result,"{");
            strcat(result,name);
            strcat(result,", ");
            strcat(result,)
            fault=1;
        }
        if(strcmp(strings1,"login") == 0)
        {
            fault =1;
        }
         if(strcmp(strings1,"createchannel") == 0)
        {
            fault =1;
        }

         if(strcmp(strings1,"joinchannel") == 0)
        {
            fault =1;
        }
         if(strcmp(strings1,"send") == 0)
        {
            fault =1;
        }
         if(strcmp(strings1,"refresh") == 0)
        {
            fault =1;
        }

         if(strcmp(strings1,"channelmembers") == 0)
        {
            fault =1;
        }
         if(strcmp(strings1,"leave") == 0)
        {
            fault =1;
        }
         if(strcmp(strings1,"logout") == 0)
        {
            fault =1;
        }
        if(fault == 0)
        {
            //send fault message
        }



        // Print buffer which contains the client message
        printf("From client: %s\t To client : ", buffer);
        memset(buffer, 0, sizeof(buffer));
        n = 0;
        // Copy server message to the buffer
        while ((buffer[n++] = getchar()) != '\n')
            ;

        // Send the buffer to client
        send(client_socket, buffer, sizeof(buffer), 0);

        // If the message starts with "exit" then server exits and chat ends
        if (strncmp("exit", buffer, 4) == 0)
        {
            printf("Server stopping...\n");
            return;
        }

    }
}

// Driver function
int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server, client;

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

    // Create and verify socket
    server_socket = socket(AF_INET, SOCK_STREAM, 6);
	if (server_socket == INVALID_SOCKET)
        wprintf(L"socket function failed with error = %d\n", WSAGetLastError() );
    else
        printf("Socket successfully created..\n");

    // Assign IP and port
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    // Bind newly created socket to given IP and verify
    if ((bind(server_socket, (SA *)&server, sizeof(server))) != 0)
    {
        printf("Socket binding failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully bound..\n");

    // Now server is ready to listen and verify
    if ((listen(server_socket, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");

    // Accept the data packet from client and verify
    int len = sizeof(client);
    client_socket = accept(server_socket, (SA *)&client, &len);
    if (client_socket < 0)
    {
        printf("Server accceptance failed...\n");
        exit(0);
    }
    else
        printf("Server acccepted the client..\n");

    // Close the socket
    closesocket(server_socket);
}
void respond_socket(int err)
{

    if (err != 0) {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

    // Create and verify socket
    server_socket = socket(AF_INET, SOCK_STREAM, 6);
	if (server_socket == INVALID_SOCKET)
        wprintf(L"socket function failed with error = %d\n", WSAGetLastError() );
    else
        printf("Socket successfully created..\n");

    // Assign IP and port
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    // Bind newly created socket to given IP and verify
    if ((bind(server_socket, (SA *)&server, sizeof(server))) != 0)
    {
        printf("Socket binding failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully bound..\n");

    // Now server is ready to listen and verify
    if ((listen(server_socket, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");

    // Accept the data packet from client and verify
    int len = sizeof(client);
    client_socket = accept(server_socket, (SA *)&client, &len);
    if (client_socket < 0)
    {
        printf("Server accceptance failed...\n");
        exit(0);
    }
    else
        printf("Server acccepted the client..\n");

}
void AuthToken_creating()
{
     /* Length of the password */
    unsigned short int length = 8;

    /* Seed number for rand() */
    srand((unsigned int) time(0));
    char *authtokening=calloc(8,sizeof(char));
    /* ASCII characters 33 to 126 */
    while(length--) {
        (authtokening++)= putchar(rand() % 94 + 33);
    }

    printf("\n");
}

