#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "common.h"
#include <stdbool.h>

uint8_t *packets[5];
int packet_sizes[5];
int set_packets = 0;

int main() {

//Data inn fra stdin hentet fra introduce_error
uint8_t *data = malloc(sizeof(uint8_t) * 100000);
    for(int i = 0; i < 5; i++) {
        packets[i] = NULL;
    }
    while(!feof(stdin)) {
        int data_read = fread(data, 1, 6, stdin);
        int data_length = get_bits(data, 16, 32) + 1;
        data_read += fread(data + 6, 1, data_length, stdin);

        // Lagre data i bufferpakke
        packets[set_packets] = malloc(data_read);
        memcpy(packets[set_packets], data, data_read);
        packet_sizes[set_packets] = data_read;
        set_packets += 1;
}

// Bubble sort sequence counter
for(int i = 0; i < set_packets - 1; i++) {
    for(int j = 0; j < set_packets - i - 1; j++) {
        if(get_bits(packets[j], 14, 18) > get_bits(packets[j + 1], 14, 18)) {
            
            // Swap packets
            uint8_t *temp_packet = packets[j];
            packets[j] = packets[j + 1];
            packets[j + 1] = temp_packet;

            //Swap packet_sizes
            int temp_size = packet_sizes[j];
            packet_sizes[j] = packet_sizes[j + 1];
            packet_sizes[j + 1] = temp_size;
        printf("swapping packets at indexes %d and %d\n", j, j +1);
        }
    }
}

// Send sorterte pakker til stdout

for(int i = 0; i < set_packets; i++) {
    int bytes_written = write(fileno(stdout), packets[i], packet_sizes[i]);
    fflush(stdout);
    packets[i] = NULL;
}

// Frigjør minne
free(data);
return 0;
}

