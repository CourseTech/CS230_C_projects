#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <stdbool.h>

int int_compare(void * num1, void * num2){
    int a = *(int *)num1;
    int b = *(int *)num2;
    if (a == b) return 0;
    if (a > b) return 1;
    else return -1;
}

int main(int argc, char * argv[]){

    // make connection to server
    int sock = socket(AF_INET, SOCK_STREAM, 0);;
    int port_num = atoi(argv[2]);;
    char *id_addr = argv[1];

    if (sock < 0){
        printf("\n Socket creation error \n");
        return -1;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_num);

    if(inet_pton(AF_INET, argv[3], &server_address.sin_addr) <= 0){
        printf("\nAddress not supported or invalid address number \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }

    printf("Connected to the server \n");

    char buff[300];
    char final_ans[100];
    
    strcpy(final_ans, "cs230 HELLO ");
    strcat(final_ans, id_addr);
    strcat(final_ans, "\n");
    printf("sent to server: %s\n", final_ans);

    if (send(sock, final_ans, strlen(final_ans), 0) < 0){
        printf("Error sending messages to sever\n");
        return -1;       
    }

    char *operator;
    char * first_val;

    while (true){
        if (recv(sock, buff, 200, 0) < 0){
            printf("Error receiving messages\n");
            return -1;
        }

        first_val = strtok(buff, " "); // unused
        char status[50];
        strcpy(status,strtok(NULL, " "));
        operator = strtok(NULL, " ");

        if (strcmp(status, "STATUS") != 0){
            return -1;
        }
        int array[5];
        for (int i = 0; i < 5; ++i){
            array[i] = atoi(strtok(NULL, " "));
        }
        qsort(array, 5, sizeof(int), int_compare);

        int ans;
        if (strcmp(operator, "max") == 0){
            ans = array[4];
        }
        else if ((strcmp(operator, "min") == 0)){
            ans = array[0];
        }
        else if ((strcmp(operator, "median") == 0)){
            ans = array[2];
        }
        else{
            printf("Invalid operator\n");
            return -1;
        }

        char str[50];

        strcpy(final_ans, "cs230 ");
        sprintf(str, "%d", ans);
        strcat(final_ans, str);
        strcat(final_ans, "\n");

        if (send(sock, final_ans, strlen(final_ans), 0) < 0){
            puts("Error sending message\n");
            return -1;
        }

    }

    return 0;

}
