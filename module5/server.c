

#define _WIN32_WINNT 0x0600
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT "8080"
#define MAX_REQUEST 256
#define MAX_CONTENT 2048

static volatile sig_atomic_t running = 1;
static SOCKET server_socket = INVALID_SOCKET;

static void handle_sigint(int sig) {
    (void)sig;
    running = 0;
    if (server_socket != INVALID_SOCKET) {
        closesocket(server_socket);
        server_socket = INVALID_SOCKET;
    }
}

static int send_all(SOCKET sock, const char *data, int length) {
    int sent = 0;
    while (sent < length) {
        int n = send(sock, data + sent, length - sent, 0);
        if (n == SOCKET_ERROR || n == 0) return 0;
        sent += n;
    }
    return 1;
}

static void handle_client(SOCKET client) {
    char filename[MAX_REQUEST];
    int used = 0;

    while (used < MAX_REQUEST - 1) {
        char ch;
        int n = recv(client, &ch, 1, 0);
        if (n <= 0) {
            closesocket(client);
            return;
        }
        if (ch == '\n') break;
        if (ch != '\r') filename[used++] = ch;
    }
    filename[used] = '\0';

    if (used == 0 || used >= MAX_REQUEST - 1 ||
        strstr(filename, "..") != NULL ||
        strchr(filename, '/') != NULL ||
        strchr(filename, '\\') != NULL ||
        strchr(filename, ':') != NULL) {
        const char *msg = "ERROR: Invalid filename.\n";
        send_all(client, msg, (int)strlen(msg));
        closesocket(client);
        return;
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        const char *msg = "ERROR: File not found or cannot be opened.\n";
        send_all(client, msg, (int)strlen(msg));
        closesocket(client);
        return;
    }

    char content[MAX_CONTENT + 1];
    size_t count = fread(content, 1, sizeof(content), file);
    int read_error = ferror(file);
    int too_large = count > MAX_CONTENT - 0;
    if (!read_error && !too_large) {
        int extra = fgetc(file);
        if (extra != EOF) too_large = 1;
        if (ferror(file)) read_error = 1;
    }
    fclose(file);

    if (read_error) {
        const char *msg = "ERROR: Could not read file.\n";
        send_all(client, msg, (int)strlen(msg));
    } else if (too_large) {
        const char *msg = "ERROR: File exceeds 2048 characters/bytes.\n";
        send_all(client, msg, (int)strlen(msg));
    } else {
        const char *header = "OK\n";
        send_all(client, header, (int)strlen(header));
        if (count > 0) send_all(client, content, (int)count);
    }
    closesocket(client);
}

int main(void) {
    WSADATA wsa;
    struct addrinfo hints, *result = NULL;
    int rc;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        return 1;
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    rc = getaddrinfo(NULL, PORT, &hints, &result);
    if (rc != 0) {
        fprintf(stderr, "getaddrinfo failed: %d\n", rc);
        WSACleanup();
        return 1;
    }

    server_socket = socket(result->ai_family, result->ai_socktype,
                           result->ai_protocol);
    if (server_socket == INVALID_SOCKET) {
        fprintf(stderr, "socket failed: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR,
               (const char *)&opt, sizeof(opt));

    if (bind(server_socket, result->ai_addr,
             (int)result->ai_addrlen) == SOCKET_ERROR) {
        fprintf(stderr, "bind failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(result);

    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
        fprintf(stderr, "listen failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    signal(SIGINT, handle_sigint);
    printf("Server listening on port %s. Press Ctrl+C to stop.\n", PORT);

    while (running) {
        SOCKET client = accept(server_socket, NULL, NULL);
        if (client == INVALID_SOCKET) {
            if (!running) break;
            fprintf(stderr, "accept failed: %d\n", WSAGetLastError());
            continue;
        }
        handle_client(client);
    }

    if (server_socket != INVALID_SOCKET) closesocket(server_socket);
    WSACleanup();
    printf("Server shut down gracefully.\n");
    return 0;
}
