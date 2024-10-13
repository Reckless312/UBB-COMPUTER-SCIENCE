#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int c;
    struct sockaddr_in server;

    if(argc < 2) {
        printf("Not enough arguments!\n");
        return 2;
    }
    c = socket(AF_INET, SOCK_STREAM, 0);

    if (c < 0) {
        printf("Eroare la crearea socketului client\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la conectarea la server\n");
        return 1;
    }

    uint16_t* data = malloc(sizeof(uint16_t) * (argc - 1));
    uint16_t suma, length;

    length = argc - 1;
    length = htons(length);
    send(c, &length, sizeof(length), 0);

    for (int i = 0; i < argc - 1; i++) {
        data[i] = atoi(argv[i + 1]);
        data[i] = htons(data[i]);
        send(c, &data[i], sizeof(data[i]), 0);
    }

    recv(c, &suma, sizeof(suma), 0);
    suma = ntohs(suma);
    printf("Suma este %hu\n", suma);

    free(data);
    close(c);
    return 0;
}