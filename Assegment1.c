#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 1. تعريف حجم المخزن الدائري
#define BUFFER_SIZE 15 

// 2. هيكل البيانات للمخزن الدائري [cite: 48, 53]
typedef struct {
    char data_array[BUFFER_SIZE]; // المصفوفة التخزينية [cite: 49]
    int write_index;              // مؤشر الكتابة (Tail) [cite: 51]
    int read_index;               // مؤشر القراءة (Head) [cite: 50]
    int current_count;            // عدد العناصر الحالية [cite: 52]
} CircularBuffer;

// 3. تهيئة المخزن عند البداية [cite: 7, 54]
void resetBuffer(CircularBuffer *cb) {
    cb->write_index = 0;
    cb->read_index = 0;
    cb->current_count = 0;
}

// 4. التحقق مما إذا كان المخزن ممتلئاً [cite: 9, 59]
bool isBufferFull(CircularBuffer *cb) {
    return cb->current_count == BUFFER_SIZE;
}

// 5. التحقق مما إذا كان المخزن فارغاً [cite: 9, 61]
bool isBufferEmpty(CircularBuffer *cb) {
    return cb->current_count == 0;
}

// 6. إضافة محرف إلى المخزن (عملية الكتابة) [cite: 8, 15, 64]
void enqueueElement(CircularBuffer *cb, char character) {
    if (isBufferFull(cb)) {
        printf("\n[Warning] Overflow: Buffer is full, cannot add '%c'\n", character); // [cite: 17, 66]
        return;
    }
    cb->data_array[cb->write_index] = character;
    cb->write_index = (cb->write_index + 1) % BUFFER_SIZE; // تحريك المؤشر دائرياً [cite: 5]
    cb->current_count++;
}

// 7. استخراج محرف من المخزن (عملية القراءة) [cite: 8, 16, 69]
char dequeueElement(CircularBuffer *cb) {
    if (isBufferEmpty(cb)) {
        printf("\n[Warning] Underflow: Buffer is empty\n"); // [cite: 17, 71]
        return '\0';
    }
    char data = cb->data_array[cb->read_index];
    cb->read_index = (cb->read_index + 1) % BUFFER_SIZE; // تحريك المؤشر دائرياً [cite: 5]
    cb->current_count--;
    return data;
}

// 8. الدالة الرئيسية لتنفيذ سيناريو الواجب [cite: 18, 76]
int main() {
    CircularBuffer myBuffer;
    resetBuffer(&myBuffer);

    char userName[100];
    const char suffix[] = "CE-ESY";

    // طلب الاسم من المستخدم [cite: 20, 80]
    printf("Please enter your name: ");
    scanf("%s", userName);

    // دمج النص المطلوب [cite: 20, 83]
    strcat(userName, suffix);
    printf("Processing string: %s\n", userName);
    printf("----------------------------------\n");

    // تخزين السلسلة في المخزن الدائري [cite: 21, 85, 86]
    for (int i = 0; i < strlen(userName); i++) {
        enqueueElement(&myBuffer, userName[i]);
    }

    // قراءة البيانات وعرضها على الشاشة [cite: 21, 87, 91]
    printf("Retrieved from buffer: ");
    while (!isBufferEmpty(&myBuffer)) {
        printf("%c", dequeueElement(&myBuffer));
    }
    printf("\n");

    // التحقق النهائي من فراغ المخزن [cite: 21]
    if (isBufferEmpty(&myBuffer)) {
        printf("Status: Buffer is now empty.\n");
    }

    return 0;
}