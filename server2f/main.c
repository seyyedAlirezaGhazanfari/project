#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "CJSON.h"
#define MAX 80
#define PORT 12345
#define SA struct sockaddr
#include <time.h>
int number;
int test1;
int numberofchannel;
int server_socket, client_socket;
struct sockaddr_in server, client;

WORD wVersionRequested;
WSADATA wsaData;
int err;
int gdad;
char *groplist[100][100];

struct name
{
    char*esm;
    char* namelist;
} zade[100]    ;
// Driver function
int main()
{
    system("COLOR F3");
    struct name;
    int i;
    for(i=0; i<100; i++)
    {
        int h;
        for(h=0; h<100; h++)
            groplist[i][h] = "mm";
    }
    char *channeltoken=calloc(100,sizeof(char));

    FILE *memberlist = fopen("memberlist.txt","a");
    fclose(memberlist);
    FILE *channellist = fopen("channellist.txt","a");
    fclose(channellist);
    FILE *message = fopen("message.txt","a");
    fclose(message);
    FILE *online = fopen("online.txt","a");
    fclose(online);
    FILE*channel = fopen("channel.txt","a");
    fclose(channel);

    creating_socket();
    char buffer[MAX];
    int n;
    char *name2=calloc(100,sizeof(char));
    char *password2=calloc(100,sizeof(char));
    char *name=calloc(100,sizeof(char));
    char *password=calloc(100,sizeof(char));
    char *token = calloc(10,1);

    while (1)
    {
        char *dastoor2 = calloc(100,1);

        test1 =0;


        char *sended=calloc(100,sizeof(char));
        char *dastoor=calloc(100,sizeof(char));
        memset(buffer, 0, sizeof(buffer));
        getting_data();

        // Read the message from client and copy it to buffer
        recv(client_socket, buffer, sizeof(buffer), 0);
        if(!(buffer == NULL))
        {

            sscanf(buffer,"%s",dastoor);














            ///////////////////////////////////////////////////////////////////////////register
            if(strcmp(dastoor,"register") == 0)
            {
                test1=0;
                char *name2 =calloc(100,sizeof(char));
                char *password2=calloc(100,sizeof(char));

                char bb;
                sscanf(buffer,"%*s%c%[^,]s",&bb,name);
                sscanf(buffer,"%*s%*s%s",password);

                memberlist = fopen("memberlist.txt","r");
                while(!feof(memberlist))
                {


                    fscanf(memberlist,"%s\t%s",name2,password2);
                    if(strcmp(name2,name) == 0 || strcmp(password2,password)==0)
                        test1 = 1;
                }
                fclose(memberlist);
                rewind(memberlist);

                if(test1 != 1)
                {

                    memberlist = fopen("memberlist.txt","a");
                    fputs(name,memberlist);
                    fputs("\t",memberlist);
                    fputs(password,memberlist);
                    fputs("\n",memberlist);
                    fclose(memberlist);
                    cJSON* type = cJSON_CreateString("Successful");
                    cJSON * natige = cJSON_CreateObject();
                    cJSON_AddItemToObject(natige,"type",type);

                    cJSON * content = cJSON_CreateString("");
                    cJSON_AddItemToObject(natige,"content",content);


                    char *t = cJSON_Print(natige);
                    printf("%s\n",t);
                    send(client_socket,t,strlen(t),0);
                }
                else
                {
                    cJSON* type = cJSON_CreateString("Error");
                    cJSON * natige = cJSON_CreateObject();
                    cJSON_AddItemToObject(natige,"type",type);

                    cJSON * content = cJSON_CreateString("this Auth Token is not correct.");
                    cJSON_AddItemToObject(natige,"content",content);


                    char *t = cJSON_Print(natige);
                    printf("%s\n",t);
                    send(client_socket,t,strlen(t),0);
                }


            }







































            ///////////////////////////////////////////////////////////////login


            if(strcmp(dastoor,"login") == 0)
            {
                int tedad=0;
                int test2=0;
                char gh;
                memset(name,0,sizeof(name));
                memset(password,0,sizeof(password));
                sscanf(buffer,"%*s%c%[^,]s",&gh,name);
                sscanf(buffer,"%*s%*s%s",password);

                memberlist = fopen("memberlist.txt","r");
                number=0;
                while(!feof(memberlist))
                {

                    fscanf(memberlist,"%s\t%s",name2,password2);
                    tedad++;
                    if(strcmp(name2,name) == 0 && strcmp(password2,password) == 0)
                    {
                        test2=1;
                        number = tedad;
                        printf("number2 : %d\n",number);
                        break;

                    }

                }
                fclose(memberlist);
                rewind(memberlist);
                if(test2 == 1)
                {
                    //auth token

                    int i=0;
                    srand(time(NULL));
                    for(i=0; i<10; i++)
                    {
                        *(token+i) =rand()%25+65;
                    }


                    online = fopen("online.txt","a");
                    fprintf(online,"%s\t%s\n",name,token);
                    fclose(online);
                    //end auth token
                    cJSON* type = cJSON_CreateString("AuthToken");
                    cJSON * natige = cJSON_CreateObject();
                    cJSON_AddItemToObject(natige,"type",type);

                    cJSON * content = cJSON_CreateString(token);
                    cJSON_AddItemToObject(natige,"content",content);


                    char *t = cJSON_Print(natige);
                    printf("%s\n",t);
                    send(client_socket,t,strlen(t),0);
                }

                else
                {

                    cJSON* type = cJSON_CreateString("Error");
                    cJSON * natige = cJSON_CreateObject();
                    cJSON_AddItemToObject(natige,"type",type);

                    cJSON * content = cJSON_CreateString("this Auth Token is not correct.");
                    cJSON_AddItemToObject(natige,"content",content);


                    char *t = cJSON_Print(natige);
                    printf("%s\n",t);
                    send(client_socket,t,strlen(t),0);
                }

            }

            printf("%s\n",sended);










            int test4=0;
            /////////////////////////////////////////////////////////////////////////// //create channel

            char *channelname=calloc(100,sizeof(char));
            char *channelname2=calloc(100,sizeof(char));
            if(strcmp(dastoor,"create") == 0)
            {
                sscanf(buffer,"%*s%s",dastoor2);
                if(strcmp(dastoor2,"channel") == 0)
                {
                    sscanf(buffer,"%*s%*s%*s%s",channeltoken);
                    online = fopen("online.txt","r");
                    while(!feof(online))
                    {
                        fscanf(online,"%s\t%s\n",name,token);
                        if(strcmp(token,channeltoken)  == 0)
                            break;
                    }
                    fclose(online);
                    rewind(online);
                    /////////////////////////////////////////////////////////////////
                    if(strcmp(token,channeltoken) == 0)
                    {
                        char sd;
                        sscanf(buffer,"%*s%*s%c%[^,]s",&sd,channelname);
                        channellist = fopen("channellist.txt","r");
                        while(!feof(channellist))
                        {
                            fscanf(channellist,"%s",channelname2);
                            if(strcmp(channelname,channelname2) == 0)
                                test4 =1;

                        }
                        fclose(channellist);
                        rewind(channellist);
                        if(test4 == 1)
                        {
                            cJSON* type = cJSON_CreateString("Error");
                            cJSON * natige = cJSON_CreateObject();
                            cJSON_AddItemToObject(natige,"type",type);

                            cJSON * content = cJSON_CreateString("this Auth Token is not correct.");
                            cJSON_AddItemToObject(natige,"content",content);


                            char *t = cJSON_Print(natige);
                            printf("%s\n",t);
                            send(client_socket,t,strlen(t),0);

                        }
                        else
                        {

                            cJSON* type = cJSON_CreateString("Successful");
                            cJSON * natige = cJSON_CreateObject();
                            cJSON_AddItemToObject(natige,"type",type);

                            cJSON * content = cJSON_CreateString("");
                            cJSON_AddItemToObject(natige,"content",content);


                            char *t = cJSON_Print(natige);
                            printf("%s\n",t);
                            send(client_socket,t,strlen(t),0);
                            channellist = fopen("channellist.txt","a");
                            fputs(channelname,channellist);
                            fputs("\n",channellist);
                            fclose(channellist);
                            message = fopen("message.txt","a");
                            fprintf(message,"server : %s created channel. %s\n",name,channelname);
                            fclose(message);
                            channel = fopen("channel.txt","a");
                            fprintf(channel,"%s\t%s\n",name,channelname);
                            fclose(channel);
                        }

                    }

                    else
                    {
                        cJSON* type = cJSON_CreateString("Error");
                        cJSON * natige = cJSON_CreateObject();
                        cJSON_AddItemToObject(natige,"type",type);

                        cJSON * content = cJSON_CreateString("this Auth Token is not correct.");
                        cJSON_AddItemToObject(natige,"content",content);


                        char *t = cJSON_Print(natige);
                        printf("%s\n",t);
                        send(client_socket,t,strlen(t),0);
                    }
                }
            }





////////////////////////////////////////////////////////////////find
            if(strcmp(dastoor,"find") == 0)
            {
                char*token2=calloc(100,1)
                            ;
                char*names2=calloc(100,1);
                char*channelnames=calloc(100,1);
                char ss;

                sscanf(buffer,"%*s%c%[^,]s",&ss,name);
                name;
                sscanf(buffer,"%*s%*s%s",token);
                online = fopen("online.txt","r");
                while(!feof(online))
                {
                    fscanf(online,"%s %s",name2,token2);
                    if(strcmp(token2,token) == 0)
                        break;
                }
                fclose(online);
                rewind(online);
                char *par=calloc(100,1);
                char*channelname = calloc(100,1);
                channel = fopen("channel.txt","r");
                while(!feof(channel))
                {
                    fscanf(channel,"%s %s",par,channelname);
                    if(strcmp(par,name2) == 0)
                        break;
                }
                fclose(channel);
                rewind(channel);
                int tala=0;
                char* kar = calloc(100,1);
                channel = fopen("channel.txt","r");
                while(!feof(channel))
                {
                    fscanf(channel,"%s %s",par,kar);
                    if(strcmp(kar,channelname) ==0 )
                    {
                        if(strcmp(name,par) == 0)
                            tala = 1;
                    }
                }
                fclose(channel);
                rewind(channel);

                if(tala == 1)
                {
                    cJSON* type = cJSON_CreateString("True");
                    cJSON * natige = cJSON_CreateObject();
                    cJSON_AddItemToObject(natige,"type",type);

                    cJSON * content = cJSON_CreateString("");
                    cJSON_AddItemToObject(natige,"content",content);


                    char *t = cJSON_Print(natige);
                    printf("%s\n",t);
                    send(client_socket,t,strlen(t),0);
                }
                else
                {
                    cJSON* type = cJSON_CreateString("False");
                    cJSON * natige = cJSON_CreateObject();
                    cJSON_AddItemToObject(natige,"type",type);

                    cJSON * content = cJSON_CreateString("");
                    cJSON_AddItemToObject(natige,"content",content);


                    char *t = cJSON_Print(natige);
                    printf("%s\n",t);
                    send(client_socket,t,strlen(t),0);
                }
            }















///////////////////////////////////////////////////////////////////////////////////////join channel
            char*namechannel=calloc(100,sizeof(char));
            if(strcmp(dastoor,"join")==0)
            {
                sscanf(buffer,"%*s%*s%*s%s",channeltoken);
                int test5 = 0;
                char*dastoor2=calloc(100,1);
                sscanf(buffer,"%*s%s",dastoor2);
                if(strcmp(dastoor2,"channel") == 0)
                {
                    online = fopen("online.txt","r");
                    while(!feof(online))
                    {
                        fscanf(online,"%s\t%s\n",name,token);
                        if(strcmp(token,channeltoken) == 0)
                            break;
                    }
                    fclose(online);
                    rewind(online);

                    if(strcmp(token,channeltoken) == 0)
                    {
                        char spsc;int kj=0;
                        sscanf(buffer,"%*s%*s%c%[^,]s",&spsc,channelname);
                        channellist = fopen("channellist.txt","r");
                        while(!feof(channellist))
                        {

                            fscanf(channellist,"%s",channelname2);

                            if(strcmp(channelname2,channelname) == 0)
                            {
                                kj=1;
                            }
                        }
                        fclose(channellist);
                        rewind(channellist);

                        ////////////////////////////////////////////////////////////////////////////////




if(kj==1){

                        cJSON* type = cJSON_CreateString("Successful");
                        cJSON * natige = cJSON_CreateObject();
                        cJSON_AddItemToObject(natige,"type",type);

                        cJSON * content = cJSON_CreateString("");
                        cJSON_AddItemToObject(natige,"content",content);


                        char *t = cJSON_Print(natige);
                        printf("%s\n",t);
                        send(client_socket,t,strlen(t),0);
                        int test6=0;
                        channel =fopen("channel.txt","a");
                        fprintf(channel,"%s\t%s\n",name,channelname);
                        fclose(channel);


                        message = fopen("message.txt","a");
                        fprintf(message,"server : %s joined. %s\n",name,channelname);
                        fclose(message);
}
else
{
    strcat(sended,"{\"");
                            strcat(sended,"type");
                            strcat(sended,"\":\"");
                            strcat(sended,"Error");
                            strcat(sended,"\",\"");
                            strcat(sended,"content");
                            strcat(sended,"\":\"\"}");
                            send(client_socket,sended,strlen(sended),0);
}


                    }//end if token

                    else
                    {
                        cJSON* type = cJSON_CreateString("Error");
                        cJSON * natige = cJSON_CreateObject();
                        cJSON_AddItemToObject(natige,"type",type);

                        cJSON * content = cJSON_CreateString("this Auth Token is not correct.");
                        cJSON_AddItemToObject(natige,"content",content);


                        char *t = cJSON_Print(natige);
                        printf("%s\n",t);
                        send(client_socket,t,strlen(t),0);

                    }


                }


            }




            /////////////////////////////////////////////////////////////////  //leave channel
            if(strcmp(dastoor,"leave") == 0)
            {
                sscanf(buffer,"%*s%s",channeltoken);
                online = fopen("online.txt","r");

                while(!feof(online))
                {
                    fscanf(online,"%s\t%s\n",name,token);
                    if(strcmp(token,channeltoken) == 0)
                        break;
                }
                fclose(online);
                rewind(online);
                if(strcmp(token,channeltoken) == 0)
                {

                    channel = fopen("channel.txt","r");
                    int i =0 ;
                    char* nam[100];
                    char *gronam[100];
                    int y;
                    while(!feof(channel))
                    {

                        fscanf(channel,"%s\t%s\n",name2,channelname2);
                        if(strcmp(name2,name) ==0)
                        {

                        }
                        else
                        {
                            nam[i] = name2;
                            gronam[i] = channelname2;
                            i++;
                        }

                    }
                    channel = fopen("channel.txt","w");
                    int u=0;
                    while(!feof(channel) && u<i)
                    {

                        fprintf(channel,"%s\t%s\n",nam[u],gronam[u]);
                        u++;
                    }
                    fclose(channel);


                    cJSON* type = cJSON_CreateString("Successful");
                    cJSON * natige = cJSON_CreateObject();
                    cJSON_AddItemToObject(natige,"type",type);

                    cJSON * content = cJSON_CreateString("");
                    cJSON_AddItemToObject(natige,"content",content);


                    char *t = cJSON_Print(natige);
                    printf("%s\n",t);
                    send(client_socket,t,strlen(t),0);

                }


                else
                {
                    cJSON* type = cJSON_CreateString("Error");
                    cJSON * natige = cJSON_CreateObject();
                    cJSON_AddItemToObject(natige,"type",type);

                    cJSON * content = cJSON_CreateString("this Auth Token is not correct.");
                    cJSON_AddItemToObject(natige,"content",content);


                    char *t = cJSON_Print(natige);
                    printf("%s\n",t);
                    send(client_socket,t,strlen(t),0);

                }




            }















            //end


















//end



//////////////////////////////////////////////////////////////////////////////////////log out
            if(strcmp(dastoor,"logout") == 0)
            {
                sscanf(buffer,"%*s%s",channeltoken);
                sscanf(buffer,"%*s%s",channeltoken);
                online = fopen("online.txt","r");

                while(!feof(online))
                {
                    fscanf(online,"%s\t%s\n",name,token);
                    if(strcmp(token,channeltoken) == 0)
                        break;
                }
                fclose(online);
                rewind(online);
                if(strcmp(channeltoken,token) == 0)
                {
                    cJSON* type = cJSON_CreateString("Successful");
                    cJSON * natige = cJSON_CreateObject();
                    cJSON_AddItemToObject(natige,"type",type);

                    cJSON * content = cJSON_CreateString("");
                    cJSON_AddItemToObject(natige,"content",content);


                    char *t = cJSON_Print(natige);
                    printf("%s\n",t);
                    send(client_socket,t,strlen(t),0);
                    char *bar[100];
                    char *bar2[100];
                    int g=0;
                    online = fopen("online.txt","r");
                    while(!feof(online))
                    {
                        fscanf(online,"%s\t%s\n",name2,token);
                        if(strcmp(name2,name) == 0 && strcmp(token,channeltoken) == 0)
                        {

                        }
                        else
                        {
                            bar[g] = name2;
                            bar2[g] = token;
                            g++;
                        }

                    }
                    fclose(online);
                    rewind(online);
                    int b =0;
                    online = fopen("online.txt","w");
                    int j =0 ;
                    while(b<g)
                    {
                        if(bar2[b] != NULL && bar[b] != NULL)
                        {
                            fprintf(online,"%s\t%s\n",bar[b],bar2[b]);
                            b++;
                        }
                        else
                            break;
                    }
                    fclose(online);

                }
                else
                {
                    cJSON* type = cJSON_CreateString("Error");
                    cJSON * natige = cJSON_CreateObject();
                    cJSON_AddItemToObject(natige,"type",type);

                    cJSON * content = cJSON_CreateString("this Auth Token is not correct.");
                    cJSON_AddItemToObject(natige,"content",content);


                    char *t = cJSON_Print(natige);
                    printf("%s\n",t);
                    send(client_socket,t,strlen(t),0);

                }
            }
//end




















            int sum =0 ;

            char *messages=calloc(100,sizeof(char));
/////////////////////////////////////////////////////////////////////////////////send message
            if(strcmp(dastoor,"send") == 0)
            {
                printf("%s\n",buffer);
                char ss;
                sscanf(buffer,"%*s%c%[^,]s",&ss,messages);

                sscanf(buffer,"%*s%*[^,]s%s",channeltoken);
                online = fopen("online.txt","r");

                while(!feof(online))
                {
                    fscanf(online,"%s\t%s\n",name,token);
                    if(strcmp(token,channeltoken) == 0)
                        break;
                }
                fclose(online);
                rewind(online);


                channel = fopen("channel.txt","r");
                while(!feof(channel))
                {
                    fscanf(channel,"%s\t%s\n",name2,channelname);
                    if(strcmp(name2,name) == 0)
                        break;
                }
                fclose(channel);
                rewind(channel);

                if(strcmp(token,channeltoken) == 0)
                {
                    {
                        cJSON* type = cJSON_CreateString("Successful");
                        cJSON * natige = cJSON_CreateObject();
                        cJSON_AddItemToObject(natige,"type",type);

                        cJSON * content = cJSON_CreateString("");
                        cJSON_AddItemToObject(natige,"content",content);


                        char *t = cJSON_Print(natige);
                        printf("%s\n",t);
                        send(client_socket,t,strlen(t),0);
                        strcat(messages,".");
                        message =fopen("message.txt","a");
                        fprintf(message,"%s : %s %s\n",name,messages,channelname);
                        fclose(message);


                    }
                }


            }

//end




























/////////////////////////////////////////////////////////////////////////channel member list
            if(strcmp(dastoor,"channel") == 0)
            {
                char x;
                sscanf(buffer,"%*s%s",dastoor2);
                if(strcmp(dastoor2,"members") == 0)
                {
                    char*token=calloc(10,1);
                    char x;
                    char *dastoor2=calloc(100,1);
                    char*name=calloc(100,1);
                    char*name2 = calloc(100,1);
                    sscanf(buffer,"%*s%s",dastoor2);
                    char* channeltoken=calloc(100,1);
                    char*channelname=calloc(100,1);
                    char*channelname2=calloc(100,1);
                    sscanf(buffer,"%*s%*s%s",channeltoken);
                    online = fopen("online.txt","r");

                    while(!feof(online))
                    {
                        fscanf(online,"%s\t%s\n",name,token);
                        if(strcmp(token,channeltoken) == 0)
                            break;
                    }
                    fclose(online);
                    rewind(online);
                    channel = fopen("channel.txt","r");
                    while(!feof(channel))
                    {
                        fscanf(channel,"%s\t%s\n",name2,channelname);
                        if(strcmp(name,name2) == 0)
                        {
                            break;
                        }
                    }
                    fclose(channel);
                    rewind(channel);




                    if(strcmp(token,channeltoken) == 0)
                    {
                        cJSON* type = cJSON_CreateString("List");
                        cJSON * natige = cJSON_CreateObject();
                        cJSON_AddItemToObject(natige,"type",type);
                        channel =fopen("channel.txt","r");
                        int h=0, jaha=0;
                        while(!feof(channel))
                        {
                            fscanf(channel,"%s\t%s\n",name2,channelname2);
                            if(strcmp(channelname2,channelname) == 0)
                            {
                                h++;
                            }
                        }
                        fclose(channel);
                        rewind(channel);


                        channel = fopen("channel.txt","r");
                        int size = 0;

                        cJSON*  content = cJSON_CreateArray();
                        content = cJSON_AddArrayToObject(natige,"content");

                        while(!feof(channel))
                        {
                            fscanf(channel,"%s\t%s\n",name2,channelname2);
                            if(strcmp(channelname2,channelname) == 0)
                            {
                                cJSON_AddItemToArray(content,cJSON_CreateString(name2));
                                char*s = cJSON_Print(content);
                            }
                        }
                        fclose(channel);
                        rewind(channel);


                        char*f = cJSON_Print(natige);
                        printf("array : %s\n",f);
                        send(client_socket,f,strlen(f),0);
                    }
                    else
                    {
                        //error cjson
                        cJSON* type = cJSON_CreateString("Error");
                        cJSON * natige = cJSON_CreateObject();
                        cJSON_AddItemToObject(natige,"type",type);

                        cJSON * content = cJSON_CreateString("this channel doesnot exist.");
                        cJSON_AddItemToObject(natige,"content",content);


                        char *t = cJSON_Print(natige);
                        printf("%s\n",t);
                        send(client_socket,t,strlen(t),0);
                        //end json
                    }

                }
            }

//end
























////////////////////////////////////////////////////////////////////////////////refresh
            if(strcmp(dastoor,"refresh") == 0)
            {


                char*token = calloc(10,1);
                char *channelname=calloc(100,sizeof(char));
                char *channelname2=calloc(100,sizeof(char));
                char*channeltoken = calloc(10,sizeof(char));
                char*name2=calloc(100,1);
                char*password2= calloc(100,1);
                char*name=calloc(100,1);
                char*password=calloc(100,1);
                sscanf(buffer,"%*s%s",token);
                online = fopen("online.txt","r");

                while(!feof(online))
                {
                    fscanf(online,"%s%s",name,channeltoken);
                    printf("a : %s\n",channeltoken);
                    if(strcmp(token,channeltoken) == 0)
                        break;
                }
                fclose(online);
                rewind(online);
                if(strcmp(token,channeltoken) == 0)
                {
                    channel = fopen("channel.txt","r");
                    while(!feof(channel))
                    {
                        fscanf(channel,"%s\t%s\n",name2,channelname);
                        if(strcmp(name2,name) == 0)
                        {
                            break;
                        }
                    }
                    fclose(channel);
                    rewind(channel);


                    message = fopen("message.txt","a");
                    fprintf(message,"server : %s refresh. %s\n",name,channelname);
                    fclose(message);

                    char *esm=calloc(100,1);
                    strcat(esm,name);
                    strcat(esm," ");
                    strcat(esm,"refresh");
                    int size =0 ;
                    char s;
                    char*l=calloc(100,1);
                    char*k=calloc(100,1);
                    char *sender=calloc(100,1);
                    char *payam=calloc(100,1);
                    char *group =calloc(100,1);
                    message = fopen("message.txt","r");
                    while(!feof(message))
                    {
                        fscanf(message,"%s",sender);
                        fscanf(message,"%s",k);
                        fscanf(message,"%c",&s);
                        fscanf(message,"%[^.]s",payam);
                        fscanf(message,"%s",l);
                        fscanf(message,"%s\n",group);
                        if(strcmp(payam,esm) == 0)
                        {
                            if(strcmp(group,channelname) == 0)
                                size++;
                        }
                    }
                    fclose(message);
                    rewind(message);
                    int shomar =0 ;
                    cJSON* type = cJSON_CreateString("List");
                    cJSON * natige = cJSON_CreateObject();
                    cJSON_AddItemToObject(natige,"type",type);
                    int thomar =0 ;
                    int dara =0;
                    ////////////////////////////////////////////////////////////////////////////////
                    message = fopen("message.txt","r");
                    while(!feof(message))
                    {
                        fscanf(message,"%s",sender);
                        fscanf(message,"%s",k);
                        fscanf(message,"%c",&s);
                        fscanf(message,"%[^.]s",payam);
                        fscanf(message,"%s",l);
                        fscanf(message,"%s\n",group);
                        if(strcmp(payam,esm) == 0)
                        {
                            if(strcmp(group,channelname) == 0)
                            {
                                thomar++;
                                if(thomar == size)
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            if(strcmp(group,channelname) == 0 && thomar == size-1)
                            {
                                dara++;
                            }
                        }
                    }
                    fclose(message);
                    rewind(message);

                    ////////////////////////////////////////////////////////////////////////////////


                    int y=0;

                    message = fopen("message.txt","r");
                    cJSON*  content = cJSON_CreateArray();
                    content = cJSON_AddArrayToObject(natige,"content");
                    while(!feof(message))
                    {
                        fscanf(message,"%s",sender);
                        fscanf(message,"%s",k);
                        fscanf(message,"%c",&s);
                        fscanf(message,"%[^.]s",payam);
                        fscanf(message,"%s",l);
                        fscanf(message,"%s\n",group);
                        if(strcmp(payam,esm) == 0)
                        {
                            if(strcmp(group,channelname) == 0)
                            {
                                shomar++;
                                if(shomar == size)
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            if(strcmp(group,channelname) == 0 && shomar == size-1 )
                            {
                                y++;
                                cJSON* pype = cJSON_CreateString(sender);
                                cJSON * katige = cJSON_CreateObject();
                                cJSON_AddItemToObject(katige,"sender",pype);

                                cJSON * sontent = cJSON_CreateString(payam);
                                cJSON_AddItemToObject(katige,"content",sontent);
                                cJSON_AddItemToArray(content,katige);
                            }
                        }


                    }
                    fclose(message);
                    rewind(message);
                    char* p = cJSON_Print(natige);
                    printf("%s\n",p);
                    send(client_socket,p,strlen(p),0);


                }


                else
                {
                    cJSON* type = cJSON_CreateString("Error");
                    cJSON * natige = cJSON_CreateObject();
                    cJSON_AddItemToObject(natige,"type",type);

                    cJSON * content = cJSON_CreateString("some problem in channel.");
                    cJSON_AddItemToObject(natige,"content",content);


                    char *t = cJSON_Print(natige);
                    printf("%s\n",t);
                    send(client_socket,t,strlen(t),0);
                }


                //end channel



            }
        }
    }
}

//function socket
void creating_socket()
{
    // Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        1;
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


}




void getting_data()
{
    // Assign IP and port
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);


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





