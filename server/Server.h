/**
 * Disclaimer
 * Most code / idea is referenced from https://github.com/Wizardous/TCP-File-Transfer
 */

// C++
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

// C
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

class Server {
private:
    int socket_descriptor;
    int after_sock_des;
    int port;
    struct sockaddr_in address;
    int address_size;
    int queue_limit;
public:
    Server();
    ~Server();
    void accept_server();
    void send_file_info();
    void receive_print();
    void receive_exec();
};