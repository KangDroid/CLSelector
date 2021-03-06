#pragma once

#include <iostream>
#include "Server.h"
#include "Client.h"
#include "configuration.h"
#if defined (__linux__)
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#endif

#if defined (__linux__)
#define DEBUG_MASTER "DEVICE_DEBUG_MASTER"
#else
#define DEBUG_MASTER "DEVICE_DEBUG_MACOS"
#endif

using namespace std;

class Device {
private:
    void init();
    bool master;
    string dev_identifier;
    string dev_addr;
    double dev_load;
    Server* exchange;

public:
    Device(string addr, Server* server_exchange);
    bool is_master();
    string get_dev_id();
    string get_dev_ip();
    double get_dev_load();
};