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

// The C-Style Includes
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

// Local Includes
#include "DeviceContainer.h"

/**
 * WARNING: THIS CONSTANT MAY NEED TO BE ADJUSTED ON LOW-MEMORY SYSTEM. THIS CONSTANT REQUIRES AT LEAST 2GB OF MEMORIES!
 * The Buffer.
 * We need to consider it's memory size.
 * How we calculate: 500 mb / sizoeof(long long), in x86_64 and g++, long long considered as 8 byte.
 */
#define BUFFER_LENGTH 65536000

using namespace std;

/**
 * WARNING: THIS FUNCTION USES LINUX/MACOS SPECIFIC FUNCTION TO RUN. WINDOWS ARE NOT SUPPORTED.
 * Copy program from "from", to "dest"
 * Returns true if copy is completed, false if not.
 */
bool copy_program(const char* from, const char* dest) {
    long long *ptr_buffer;
    long long *buffer_tmp = new long long[BUFFER_LENGTH];
    int from_fd = open(from, O_RDWR | O_EXCL, S_IRWXG | S_IRWXO | S_IRWXU);
    int dest_fd = open(dest, O_RDWR | O_CREAT | O_TRUNC, S_IRWXG | S_IRWXO | S_IRWXU);
    int read_byte, write_byte;

    if (from_fd == -1 || dest_fd == -1) {
        perror("Error occured when opening file: ");
        return false;
    }

    // Copy to buffer
    while (true) {
        while (true) {
            read_byte = read(from_fd, buffer_tmp, BUFFER_LENGTH);
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

/**
 * Input: Program File Path
 * 
 * Select, Push, Execute
 */
int main(int argc, char** argv) {
    // TODO: These location_destination should only contains NFS Folder, not image itself.
    const string location_destination = "/Users/KangDroid/Desktop/process_copied";

    // Let selected device as "master_device"
    // TODO: Dynamically select devicess
    DeviceContainer master_device;

    // If argument is less than 2
    if (argc != 2) {
        cerr << "Program usage: " << argv[0] << " \"Program_Image_Path\"" << endl;
        return -1;
    }

    // Check argv[0] is a valid path
    filesystem::path path_directory(argv[1]);
    if (!filesystem::exists(path_directory)) {
        cerr << "Request file: " << filesystem::absolute(path_directory) << " does not exists." << endl;
        return -1;
    }

    // Copy Program to destination
    copy_program(argv[1], location_destination.c_str());
}