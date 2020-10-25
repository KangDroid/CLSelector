#include <iostream>
#include "Server.h"

using namespace std;

int main(void) {
    Server server;
    int counter = 0;
    while (counter < 10) {
        server.receive_exec();
        counter++;
    }
    return 0;
}