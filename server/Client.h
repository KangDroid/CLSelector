/**
 * Disclaimer
 * Most code / idea is referenced from https://github.com/Wizardous/TCP-File-Transfer
 * 
 * TODO: Receive Command argument, Fork call to execution[execlp]
 */

// C++
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// C
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

class Client {
private:
    int port;
    int socket_descriptor;
    struct sockaddr_in address;
    int address_size;
    bool init();
    string server_addr;

public:
    Client(string sa);
    void receive_print();
    void send_file_info();
    void send_string(string to_send);
};