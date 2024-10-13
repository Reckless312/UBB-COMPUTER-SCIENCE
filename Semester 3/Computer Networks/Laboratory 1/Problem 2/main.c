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

    c = socket(AF_INET, SOCK_STREAM, 0);

    if (c < 0) {
        printf("Eroare la crearea socketului client\n");
        return 2;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la conectarea la server\n");
        return 1;
    }

    char string [1024];

    fgets(string, sizeof(string), stdin);

    uint16_t length = strlen(string), nlength = htons(length);

    send(c, &nlength, sizeof(nlength), 0);

    send(c, string, length, 0);

    uint16_t spaces;
    recv(c, &spaces, sizeof(spaces), 0);
    spaces = ntohs(spaces);
    printf("Spaces: %d\n", spaces);

    close(c);
    return 0;
}