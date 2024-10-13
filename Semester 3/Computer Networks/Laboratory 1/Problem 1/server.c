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
        uint16_t suma = 0, length, a;
        printf("Waiting for connections...\n");
        c = accept(s, (struct sockaddr *)&client, (socklen_t*)&l);
        err = errno;
        if(c < 0) {
            printf("Error accepting connections: %d\n", err);
            continue;
        }
        printf("Connection accepted from: %s.%d\n",inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        int res = recv(c, (char*)&length, sizeof(a), 0);
        if(res != sizeof(a)) printf("Error receiving length\n");
        length = ntohs(length);

        for(int i = 0; i < length; i++) {
            res = recv(c, (char*)&a, sizeof(a), 0);
            if(res != sizeof(a)) printf("Error receiving data\n");
            a = ntohs(a);
            suma += a;
        }

        suma = htons(suma);
        res = send(c, (char*)&suma, sizeof(suma), 0);
        if(res != sizeof(suma)) printf("Error sending suma\n");
        closesocket(c);
    }
}