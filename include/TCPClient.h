#pragma once

#include <string>
#include <netinet/in.h>

class TCPClient {
private:
    constexpr const static int RECVBUFSZ = 4096;
    // fd is -1 if unconnected
    int fd;
    sockaddr_in sin;
    char recvbuf[RECVBUFSZ];

public:
    TCPClient(const std::string addrin, short portin);
    ~TCPClient();

    // return true on success, false otherwise
    bool m_connect();

    // return empty string if error or received empty string (connection closed)
    std::string m_receive();

    // return false if fail, true if not fail
    bool m_send(const std::string &data);

    void m_close();
};