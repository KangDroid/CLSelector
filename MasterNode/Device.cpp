#include "Device.h"

Device::Device(string address, Server* server_exchange) {
    this->exchange = server_exchange;
    this->dev_addr = address;
    this->init();
}

void Device::init() {
    // Normally, we need to get device info from somewhere, but for now, use
    // sandbox state.
    if (this->dev_addr == "127.0.0.1") {
        this->master = true;
        this->dev_identifier = "jetson-master";
        int tmp_output = -1;
        syscall(291, &tmp_output);
        if (tmp_output == -1) {
            perror("Error occured when calling syscall 291: ");
            exit(-1);
        }
        this->dev_load = (double)tmp_output;
        return;
    }
    Client cl(this->dev_addr, SUBNODE_ACCEPT_PORT);
    cl.send_string("get_info");
    string return_value = this->exchange->get_info();
    string hostname = return_value.substr(0, return_value.find(", "));
    string load_instr = return_value.substr(return_value.find(", ")+2, return_value.length());
    this->dev_load = stoi(load_instr);
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