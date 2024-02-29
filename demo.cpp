#include <iostream>
#include "TCPClient.h"

using namespace std;

int main() {
    TCPClient c("sina.com", 80);
    if (!c.m_connect()) { return 1; }
    if (!c.m_send("hahaha")) { return 1; }
    string databack = c.m_receive();
    cout << databack << endl;
}