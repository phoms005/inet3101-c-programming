#define _WIN32_WINNT 0x0600
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT "8080"
#define MAX_FILENAME 256

int main(void) {
    WSADATA wsa;
    struct addrinfo hints, *result = NULL;
    SOCKET sock = INVALID_SOCKET;
    char filename[MAX_FILENAME];
    char buffer[1024];
    int rc;

    printf("Enter filename to request: ");
    if (!fgets(filename, sizeof(filename), stdin)) {
        fprintf(stderr, "ERROR: Could not read filename.\n");
        return 1;
    }

    filename[strcspn(filename, "\r\n")] = '\0';
    if (filename[0] == '\0' || strchr(filename, '\n') != NULL) {
        fprintf(stderr, "ERROR: Invalid filename.\n");
        return 1;
    }

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        fprintf(stderr, "ERROR: WSAStartup failed.\n");
        return 1;
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    rc = getaddrinfo("127.0.0.1", PORT, &hints, &result);
    if (rc != 0) {
        fprintf(stderr, "ERROR: Could not resolve server (%d).\n", rc);
        WSACleanup();
        return 1;
    }

    sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "ERROR: socket failed (%d).\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    if (connect(sock, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        fprintf(stderr, "ERROR: Could not connect to server. Is it running?\n");
        closesocket(sock);
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(result);

    strcat(filename, "\n");
    if (send(sock, filename, (int)strlen(filename), 0) == SOCKET_ERROR) {
        fprintf(stderr, "ERROR: Failed to send request.\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("\nServer response:\n");
    int n;
    while ((n = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        if (fwrite(buffer, 1, (size_t)n, stdout) != (size_t)n) {
            fprintf(stderr, "\nERROR: Failed to print response.\n");
            break;
        }
    }
    if (n == SOCKET_ERROR) {
        fprintf(stderr, "\nERROR: Failed to receive response.\n");
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
