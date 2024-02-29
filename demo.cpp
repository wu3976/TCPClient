#include <iostream>
#include "TCPClient.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main() {
    TCPClient c("localhost", 5005);
    if (!c.m_connect()) { return 1; }

    // read in a file
    int file_d = open("text.txt", O_RDWR);
    if (file_d == -1) {
        perror("open");
        return 1;
    }

    char buf[4096];
    memset(buf, 0, 4096);
    int nread = read(file_d, buf, 4096);
    if (nread == -1) {
        perror("read");
        return 1;
    }
    string data(buf, buf + nread);
    if (!c.m_send(data)) { return 1; }
    string databack = c.m_receive();
    cout << databack << endl;
}