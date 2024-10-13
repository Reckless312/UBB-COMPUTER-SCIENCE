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
        uint16_t length, spaces;
        char* buffer;

        printf("Waiting for connections...\n");
        c = accept(s, (struct sockaddr *)&client, (socklen_t*)&l);
        err = errno;
        if(c < 0) {
            printf("Error accepting connections: %d\n", err);
            continue;
        }
        printf("Connection accepted from: %s.%d\n",inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        int res = recv(c, (char*)&length, sizeof(length), 0);
        if(res != sizeof(length)) {printf("Error receiving length");}

        length = ntohs(length);
        buffer = malloc(sizeof(char) * length + 1);

        recv(c, buffer, length * sizeof(char), 0);
        buffer[length] = '\0';

        spaces = 0;
        for(int i = 0; i < length; i++) {
            if(buffer[i] == ' ') {
                spaces++;
            }
        }

        free(buffer);

        spaces = htons(spaces);
        res = send(c, (char*)&spaces, sizeof(spaces), 0);
        if(res!= sizeof(spaces)) {printf("Error sending data");}
        closesocket(c);
    }
}