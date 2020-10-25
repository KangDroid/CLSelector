#include "Client.h"
Client::Client() {
    int counter = 0;
    while (counter < 10) {
        if (!(this->init())) {
            cerr << "Error occured when initializing client. Trying again.." << endl;
            sleep(1);
            counter++;
        } else {
            break;
        }
    }

    if (counter == 10) {
        cerr << "Cannot create client. Exiting" << endl;
        exit(-1);
    }
}

bool Client::init() {
    // Create Socket
    this->socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket_descriptor == -1) {
        perror("Error occured: ");
        return false;
    }

    // Set Port
    this->port = 8060;

    // Setup Address[sockaddr_in struct]
    this->address.sin_family = AF_INET;
    this->address.sin_port = htons(port);
    address_size = sizeof(this->address);

    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) != 1) {
        cerr << "Error occured" << endl;
        return false;
    }

    // Connect to server
    if (connect(socket_descriptor, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Error occured when connecting to server: ");
        return false;
    }
    return true;
}

void Client::receive_print() {
    size_t buffer_size = 1073741824; // a gigabyte
    char* buffer = new char[buffer_size];
    int read_val = read(socket_descriptor, buffer, buffer_size);
    buffer[read_val-1] = 0;
    cout << buffer << endl;
    delete[] buffer;
}

void Client::send_file_info() {
    // for now, let file size = 4kb
    string size_file = "3kb";
    int sent = send(socket_descriptor, size_file.c_str(), size_file.length(), 0);
    if (sent == -1) {
        perror("Error occured when sending information to server: ");
    }
}