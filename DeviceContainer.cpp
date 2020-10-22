#include "DeviceContainer.h"

DeviceContainer::DeviceContainer() {
    this->init();
}

void DeviceContainer::init() {
    // Normally, we need to get device info from somewhere, but for now, use
    // sandbox state.
    this->master = true;
    this->dev_identifier = DEBUG_MASTER;
    this->dev_load = 1.0;
}

bool DeviceContainer::is_master() {
    return this->master;
}
string DeviceContainer::get_dev_id() {
    return this->dev_identifier;
}
double DeviceContainer::get_dev_load() {
    return this->dev_load;
}