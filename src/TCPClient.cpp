#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "TCPClient.h"

TCPClient::TCPClient(const std::string addrin, short portin) : fd(-1) {
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->fd == -1) {
        perror("socket");
        return;
    }
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(portin);
    hostent *hent = gethostbyname(addrin.c_str()); // resolve hostname
    if (!hent) {
        perror("gethostbyname");
        return;
    }
    memcpy(&sin.sin_addr, hent->h_addr, hent->h_length);
}

bool TCPClient::m_connect() {
    if (connect(fd, (sockaddr *)&sin, sizeof(sin)) == -1) {
        perror("connect");
        return false;
    }
    return true;
}

std::string TCPClient::m_receive() {
    memset(recvbuf, 0, RECVBUFSZ);
    int n_read = recv(fd, (void *)recvbuf, RECVBUFSZ, 0);
    if (n_read == -1) {
        perror("recv");
        return "";
    } else if (n_read == 0) { // connection closed by server
        std::cerr << "connection closed by server" << std::endl;
        m_close();
        return "";
    }
    return std::string(recvbuf, recvbuf + n_read);
}

bool TCPClient::m_send(const std::string &data) {
    if (send(fd, data.c_str(), data.size(), 0) == -1) {
        perror("send");
        return false;
    }
    return true;
}

TCPClient::~TCPClient() {
    m_close();
}

void TCPClient::m_close() {
    close(this->fd);
}

