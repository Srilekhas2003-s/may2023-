
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

// CRC algorithm implementation
uint16_t calculate_crc(const uint8_t* data, uint8_t length) {
    uint16_t crc = 0xFFFF; // Initialize CRC value

    for (uint8_t i = 0; i < length; i++) {
        crc ^= data[i];

        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ 0xA001; // XOR with polynomial (0xA001 for CRC-16)
            } else {
                crc = crc >> 1;
            }
        }
    }

    return crc;
}
int main(){
// Function to check if a data packet is corrupted
int is_packet_corrupted(const data_packet_t* packet) {
    // Calculate the CRC for the packet's data
    uint16_t calculated_crc = calculate_crc(packet->data, packet->data_length);

    // Compare the calculated CRC with the stored CRC in the packet
    if (calculated_crc == packet->crc) {
        // CRC matches, packet is not corrupted
        return 0;
    } else {
        // CRC does not match, packet is corrupted
        return 1;
    }
  }
}
