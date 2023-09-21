printf(" Sequence counter [%d]", get_bits(data, 14, 18));

#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

uint8_t *error_buffer = NULL;
int error_buffer_size = 0;

void fix_error(uint8_t *packet, int packet_size) {
    if (error_buffer != NULL && error_buffer_size > 0) {
        if (packet_size == error_buffer_size) {
            memcpy(packet, error_buffer, packet_size);
        }
    }
}

int main() {
    uint8_t *data = malloc(sizeof(uint8_t) * 100000);

    while (!feof(stdin)) {
        // Leser header
        int header_size = fread(data, 1, 6, stdin);
        // Leser lengda
        int data_length = get_bits(data, 16, 32) + 1;
        // Leser pakka
        int packet_size = header_size + data_length;
        int data_read = fread(data + header_size, 1, data_length, stdin);
        // Korrigering
        fix_error(data + header_size, data_length);
        int bytes_written = write(fileno(stdout), data, packet_size);
        fflush(stdout);
    }

    free(data);
    return 0;
}












//fix_error:
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




//Data ut fra stdout fra introduce_error
        
        
        int bytes_written = write(fileno(stdout), data, data_read);
        fflush(stdout);
    

    }
}

//Lag algoritme for å sortere packets med bubbles?









//Siste versjon av fix_error uten algoritme:
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

    }


//Data ut fra stdout fra introduce_error
        
        
    if(set_packets == 5) {
    for(int i = 0; i < 5; i++) {
        int bytes_written = write(fileno(stdout), packets[i], packet_sizes[i]);
        fflush(stdout);
        packets[i] = NULL;
    

    }
}
    
}
//Lag algoritme for å sortere packets med bubbles?



