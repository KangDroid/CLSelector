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

#pragma once

/**
 * WARNING: THIS CONSTANT MAY NEED TO BE ADJUSTED ON LOW-MEMORY SYSTEM. THIS CONSTANT REQUIRES AT LEAST 2GB OF MEMORIES!
 * The Buffer when copying file over somewhere.
 * We need to consider it's memory size.
 * How we calculate: 500 mb / sizoeof(long long), in x86_64 and g++, long long considered as 8 byte.
 */
#define FILE_BUFFER_LENGTH 65536000

/**
 * Buffer getting host name
 * 4096 char array would be enought to get host name, hopefully.
 */
#define HOST_NAME_BUFFER 4096

/**
 * Subnode - opened port. Used when master sending execution information.
 */
#define SUBNODE_ACCEPT_PORT 8060

/**
 * Master Node - opened port. Used when Subnode sending its load/host information.
 */
#define MASTER_ACCEPT_PORT 5050

/**
 * Master Node Address
 */
#define MASTER_ADDRESS "192.168.0.8"

/**
 * CPU Count
 * This is used when calculating NR_RUNNING from kernel.
 * There is protection when cpu's number is invalid, but anyway MATCH WITH KERNEL CONFIGURATION
 * In this program, we use jetson nano, therefore its value would be 4.
 */
#define TOTAL_CPU 4