/* 
 * Copyright (c) 2020 KangDroid, aka Jason.HW.Kang[HyunWoo Kang]
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// The C++ Includes
#include <iostream>
#include <filesystem>
#include <vector>

// The C-Style Includes
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

// Local Includes
#include "Device.h"
#include "Client.h"
#include "Server.h"
#include "configuration.h"

using namespace std;

/**
 * WARNING: THIS FUNCTION USES LINUX/MACOS SPECIFIC FUNCTION TO RUN. WINDOWS ARE NOT SUPPORTED.
 * Copy program from "from", to "dest"
 * Returns true if copy is completed, false if not.
 */
bool copy_program(const char* from, const char* dest) {
    long long *ptr_buffer;
    long long *buffer_tmp = new long long[FILE_BUFFER_LENGTH];
    int from_fd = open(from, O_RDONLY | O_EXCL, S_IRWXG | S_IRWXO | S_IRWXU);
    int dest_fd = open(dest, O_RDWR | O_CREAT | O_TRUNC, S_IRWXG | S_IRWXO | S_IRWXU);
    int read_byte, write_byte;

    if (from_fd == -1 || dest_fd == -1) {
        perror("Error occured when opening file: ");
        return false;
    }

    // Copy to buffer
    while (true) {
        while (true) {
            read_byte = read(from_fd, buffer_tmp, FILE_BUFFER_LENGTH);
            if (read_byte != -1) {
                break;
            } else if (read_byte == -1 && errno == EINTR) {
                continue;
            } else {
                perror("Error occured: ");
                return -1;
            }
        }

        ptr_buffer = buffer_tmp;

        while (true) {
            write_byte = write(dest_fd, ptr_buffer, read_byte);
            if (write_byte != -1) {
                if (write_byte != read_byte) {
                    printf("Write and read isn't same\n");
                    ptr_buffer += write_byte; // Since write didn't till read_byte, so adjust tmp_buffer_tw
                    read_byte -= write_byte; // Trivial with above line.
                } else {
                    break; // Successfully written to file
                }
            } else if (write_byte == -1 && errno == EINTR) {
                continue;
            } else {
                perror("Error occured: ");
                return -1;
            }
        }

        cout << "Read " << read_byte << " bytes, Wrote " << write_byte << " bytes." << endl;
        // If read byte is zero, end of file reached, which means we don't have to write.
        if (read_byte == 0) {
            cout << "Copied successfully." << endl;
            break;
        }
    }

    close(from_fd);
    close(dest_fd);
    delete[] buffer_tmp;
    return true;
}

bool compare(Device dev_one, Device dev_two) {
    if (dev_one.get_dev_load() == dev_two.get_dev_load()) {
        if (dev_one.get_dev_id() == "jetson-master" ) {
            return 1;
        }
    } else {
        return dev_one.get_dev_load() < dev_two.get_dev_load();
    }
}

/**
 * Input: Program File Path
 * 
 * Select, Push, Execute
 */
int main(int argc, char** argv) {
    // TODO: These location_destination should only contains NFS Folder.
    #if defined(__linux__)
    const string location_destination = "/home/kangdroid/node_share/";
    #else
    const string location_destination = "/Users/KangDroid/Desktop/";
    #endif

    // If argument is less than 2
    if (argc != 2) {
        cerr << "Program usage: " << argv[0] << " \"Program_Image_Path\"" << endl;
        return -1;
    }

    filesystem::path path_directory(argv[1]);
    // Check argv[0] is a valid path
    if (!filesystem::exists(path_directory)) {
        cerr << "Request file: " << filesystem::absolute(path_directory) << " does not exists." << endl;
        return -1;
    }

    pid_t copy_process = fork();
    if (copy_process == 0) {
        // Copy Program to destination
        copy_program(argv[1], (location_destination + path_directory.filename().string()).c_str());
    }

    // Initiate Device
    // Open Server
    Server server_infochange(MASTER_ACCEPT_PORT);
    vector<Device> device_container;
    ifstream ifs("node.txt");
    if (!ifs.is_open()) {
        cerr << "Node information file is not opened. " << endl;
        return -1;
    }
    string buffer;
    cout << "Checking device" << endl;
    while (getline(ifs, buffer)) {
        cout << buffer << endl;
        device_container.push_back(Device(buffer, &server_infochange));
    }
    
    if (device_container.size() > 1) {
        sort(device_container.begin(), device_container.end(), compare);
    }

    // Init: Debug Information
    for (int i = 0; i < device_container.size(); i++) {
        cout << "IP: " << device_container[i].get_dev_ip() << endl;
        cout << "Load CTR: " << device_container[i].get_dev_load() << endl;
    }

    // Let selected device as "master_device"
    Device* selected = &device_container[0];
    // Wait for fork - child process
    wait(NULL);

    // exec program.
    if (selected->get_dev_ip() == "127.0.0.1") {
        pid_t tmp_pid = fork();
        string to_ex = (location_destination + path_directory.filename().string());
        if (tmp_pid == 0) {
            execl(to_ex.c_str(), to_ex.c_str(), NULL);
        } else {
            wait(NULL);
        }
    } else {
        Client cl(selected->get_dev_ip(), SUBNODE_ACCEPT_PORT);
        cl.send_string((location_destination + path_directory.filename().string()));
    }
}