#include <iostream>

#define DEBUG_MASTER "DEVICE_DEBUG_MACOS"

using namespace std;

class DeviceContainer {
private:
    void init();
    bool master;
    string dev_identifier;
    double dev_load;

public:
    DeviceContainer();
    bool is_master();
    string get_dev_id();
    double get_dev_load();
};