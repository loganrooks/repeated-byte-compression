#include <iostream>


bool checkRepeats(uint8_t byte) {
    return (0x80 & byte) != 0;
}

void insertRepeats(uint8_t byte, int numRepeats, uint8_t dataPtr[]) {
    for (int i = 0; i < numRepeats; i++) {
        dataPtr[i] = byte;
    }
}

uint8_t numberOfContigRepeats(uint8_t *dataPtr, int dataSize) {
    uint8_t numRepeats = 0; int i = 0;
    while ((dataPtr[i] == dataPtr[i+1]) && (i < dataSize - 1) && (i < 255)) {
        numRepeats++;
        i++;
    }
    return numRepeats;
}

void resizeArray(int newSize, int arraySize, uint8_t *array[]) {
    uint8_t newArray[newSize];
    uint8_t * newArrayPtr = newArray;

    for (int i = 0; i < arraySize; i++) {
        newArray[i] = (*array)[i];
    }

    array = &newArrayPtr;
}
