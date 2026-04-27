#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define BUFFER_SIZE 10

typedef struct {
    char data_array[BUFFER_SIZE]; 
    int write_index;              
    int read_index;             
    int current_count;            
} CircularBuffer;

void resetBuffer(CircularBuffer *cb) {
    cb->write_index = 0;
    cb->read_index = 0;
    cb->current_count = 0;
}

bool isBufferFull(CircularBuffer *cb) {
    return cb->current_count == BUFFER_SIZE;
}

bool isBufferEmpty(CircularBuffer *cb) {
    return cb->current_count == 0;
}

void enqueueElement(CircularBuffer *cb, char character) {
    if (isBufferFull(cb)) {
        printf("\n[Warning] Overflow: Buffer is full, cannot add '%c'\n", character); 
        return;
    }
    cb->data_array[cb->write_index] = character;
    cb->write_index = (cb->write_index + 1) % BUFFER_SIZE; 
    cb->current_count++;
}

char dequeueElement(CircularBuffer *cb) {
    if (isBufferEmpty(cb)) {
        printf("\n[Warning] Underflow: Buffer is empty\n"); 
        return '\0';
    }
    char data = cb->data_array[cb->read_index];
    cb->read_index = (cb->read_index + 1) % BUFFER_SIZE; 
    cb->current_count--;
    return data;
}

int main() {
    CircularBuffer myBuffer;
    resetBuffer(&myBuffer);

    char userName[100];
    const char suffix[] = "CE-ESY";

    printf("Please enter your name: ");
    scanf("%s", userName);

    strcat(userName, suffix);
    printf("Processing string: %s\n", userName);
    printf("----------------------------------\n");

    for (int i = 0; i < strlen(userName); i++) {
        enqueueElement(&myBuffer, userName[i]);
    }

    printf("Retrieved from buffer: ");
    while (!isBufferEmpty(&myBuffer)) {
        printf("%c", dequeueElement(&myBuffer));
    }
    printf("\n");

    if (isBufferEmpty(&myBuffer)) {
        printf("Status: Buffer is now empty.\n");
    }

    return 0;
}
