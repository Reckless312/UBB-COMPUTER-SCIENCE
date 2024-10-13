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

    uint16_t num;

    scanf("%hd", &num);
    num = htons(num);
    send(c, &num, sizeof(num), 0);

    uint16_t total_div;

    recv(c, &total_div, sizeof(total_div), 0);

    total_div = ntohs(total_div);

    uint16_t* div = malloc(total_div * sizeof(uint16_t));

    for (int i = 0; i < total_div; i++) {
        recv(c, &div[i], sizeof(div[i]), 0);
        div[i] = ntohs(div[i]);
        printf("Received: %d\n", div[i]);
    }
    printf("Total divizors: %d\n", total_div);

    free(div);

    close(c);
    return 0;
}