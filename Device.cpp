#include "Device.h"

Device::Device(string address) {
    this->dev_addr = address;
    this->init();
}

void Device::init() {
    // Normally, we need to get device info from somewhere, but for now, use
    // sandbox state.
    this->master = true;
    this->dev_identifier = DEBUG_MASTER;
    #if defined(__linux__)
    int tmp_output = -1;
    syscall(291, &tmp_output);
    if (tmp_output == -1) {
        perror("Error occured when calling syscall 291: ");
        exit(-1);
    }
    this->dev_load = (double)tmp_output;
    #else
    this->dev_load = 0;
    #endif
}

bool Device::is_master() {
    return this->master;
}
string Device::get_dev_id() {
    return this->dev_identifier;
}
double Device::get_dev_load() {
    return this->dev_load;
}

string Device::get_dev_ip() {
    return this->dev_addr;
}