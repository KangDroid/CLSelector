#include "Server.h"

Server::Server(int port) {
    // Set initial variable
    this->queue_limit = 5;

    // Create Socket
    this->socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket_descriptor == -1) {
        perror("Error occured: ");
        exit(-1);
    }

    // Reuse socket created by master
    int tmp = 1;
    setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(int));

    // Set Port
    this->port = port;

    // Setup Address[sockaddr_in struct]
    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = INADDR_ANY;
    this->address.sin_port = htons(port);
    address_size = sizeof(this->address);

    // Bind Socket
    int ret_val = ::bind(socket_descriptor, (struct sockaddr *)&address, sizeof(address));
    if (ret_val == -1) {
        // errno set.
        perror("Error occured when binding: ");
        exit(-1);
    }

    // Listen!
    if (listen(socket_descriptor, queue_limit) == -1) {
        perror("Error occured when listening: ");
        exit(-1);
    } else {
        cout << "Server: Waiting.." << endl;
    }
}

void Server::accept_server() {
    // Accept if connection exists
    after_sock_des = accept(socket_descriptor, (struct sockaddr *)&address, (socklen_t*)&address_size);
    if (after_sock_des == -1) {
        cerr << "Accept failed" << endl;
        exit(-1);
    }
}

Server::~Server() {
    close(after_sock_des);
    close(socket_descriptor);
}

// Server --> Client
void Server::send_file_info() {
    // for now, let file size = 4kb
    string size_file = "3kb";
    int sent = send(after_sock_des, size_file.c_str(), size_file.length(), 0);
}

// Client --> Server
void Server::receive_print() {
    accept_server();
    size_t buffer_size = 1073741824; // a gigabyte
    char* buffer = new char[buffer_size];
    int read_val = read(after_sock_des, buffer, buffer_size);
    buffer[read_val] = 0;
    cout << buffer << endl;
    delete[] buffer;
}

string Server::get_info() {
    accept_server();
    size_t buffer_size = 1073741824; // a gigabyte
    char* buffer = new char[buffer_size];
    int read_val = read(after_sock_des, buffer, buffer_size);
    buffer[read_val] = 0;
    string ret_val = string(buffer);
    delete[] buffer;
    return ret_val;
}

void Server::receive_exec() {
    accept_server();
    size_t buffer_size = 1073741824; // a gigabyte
    char* buffer = new char[buffer_size];
    int read_val = read(after_sock_des, buffer, buffer_size);
    buffer[read_val] = 0;
    // In this stage, all commands are transferred.

    pid_t pid_what = fork();

    if (pid_what == 0) {
        // child
        execl(buffer, buffer, NULL);
    } else {
        wait(NULL);
    }
    delete[] buffer;
}
