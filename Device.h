#include <iostream>

#define DEBUG_MASTER "DEVICE_DEBUG_MACOS"

using namespace std;

class Device {
private:
    void init();
    bool master;
    string dev_identifier;
    double dev_load;

public:
    Device();
    bool is_master();
    string get_dev_id();
    double get_dev_load();
};