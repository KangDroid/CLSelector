#include <iostream>
#include "Server.h"

using namespace std;

// Maximum command to print/execute
#define MAXIMUM_COUNT 10

/**
 * Server Program.
 * If main function uses receive_exec(), it means it will execute every command sent from client.
 * If main function uses receive_print(), it means it will just print out every command sent from client.
 */

int main(void) {
    Server server;
    int counter = 0;
    while (counter < MAXIMUM_COUNT) {
        server.receive_exec();
        counter++;
    }
    return 0;
}