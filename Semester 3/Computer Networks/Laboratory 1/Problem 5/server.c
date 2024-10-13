#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define closesocket close

typedef int SOCKET;


int main() {
    SOCKET s;
    struct sockaddr_in server, client;
    int c, l, err;

    s = socket(AF_INET, SOCK_STREAM, 0);

    if(s < 0) {
        printf("Error opening socket\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Binding failed");
        return 2;
    }

    listen(s, 5);

    l = sizeof(client);
    memset(&client, 0, sizeof(client));

    while(1) {
        uint16_t total, div, num;

        printf("Waiting for connections...\n");
        c = accept(s, (struct sockaddr *)&client, (socklen_t*)&l);
        err = errno;
        if(c < 0) {
            printf("Error accepting connections: %d\n", err);
            continue;
        }
        printf("Connection accepted from: %s.%d\n",inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        total = 0;
        recv(c, &num, sizeof(num), 0);
        num = ntohs(num);
        int i = 1;
        while(i * i < num) {
            if(num % i == 0) {
                total += 2;
            }
            i++;
        }
        if(i * i == num) {
            total++;
        }
        total = htons(total);
        send(c, &total, sizeof(total), 0);

        i = 1;
        while(i * i < num) {
            if(num % i == 0) {
                div = i;
                div = htons(div);
                send(c, &div, sizeof(div), 0);
                div = num / i;
                div = htons(div);
                send(c, &div, sizeof(div), 0);
            }
            i++;
        }
        if(i * i == num) {
            div = i;
            div = htons(div);
            send(c, &div, sizeof(div), 0);
        }
        closesocket(c);
    }
}