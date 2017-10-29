#include <iostream>
using namespace std;



bool checkRepeats(char byte) {
    return (0x80 & byte) != 0;
}

void insertRepeats(char byte, int numRepeats, char dataPtr[]) {
    for (int i = 0; i < numRepeats; i++) {
        dataPtr[i] = byte;
    }
}

int numberOfContigRepeats(char *dataPtr) {
    int numRepeats = 0; int i = 0;
    while (dataPtr[i] == dataPtr[i+1]) {
        numRepeats++;
        i++;
    }
    return numRepeats;
}

char* resizeArray(int newSize, char array[]) {

}

int byteCompress(char dataPtr[], int dataSize) {
    int compressedSize = 0; int i = 0; int j = 0;
    while (i < dataSize){
        int numRepeats = numberOfContigRepeats(&dataPtr[i]);
        if (numRepeats > 0) {
            // Modify MSB of entry to indicate repetition
            dataPtr[j] = dataPtr[i] | char(0x80);
            // Store the amount of repetition
            dataPtr[j+1] = char(numRepeats);
            compressedSize += 1;
            // Update pre-compression index to skip repetitions
            // Update compression index to skip added repetition number
            i += numRepeats;
            j++;
        }
        else {
            dataPtr[j] = dataPtr[i];
        }

        compressedSize += 1; i++; j++;
    }
    return compressedSize;
}

int byteDecompress(char compressedData[], int compressedSize) {
    int dataSize = 0; int j = 0;
    int tempSize = 2*compressedSize;
    char tempDataPtr[tempSize];
    for (int i = 0; i < compressedSize; i++) {
        tempDataPtr[j] = char(compressedData[i] ^ 0x80);
        if (checkRepeats(compressedData[i])) {
            int numRepeats = compressedData[i+1];
            insertRepeats(tempDataPtr[j], numRepeats, &tempDataPtr[j+1]);
            dataSize += numRepeats;
            i++; j+= numRepeats;
        }
        i++; j++;
        dataSize++;
        if (dataSize >= tempSize) {
            tempSize*=2;
            tempDataPtr = resizeArray(tempSize, tempDataPtr);
        }

    }

}

int main() {
    char dataPtr[] = { 0x03, 0x74, 0x04, 0x04, 0x04, 0x35, 0x35, 0x64,
                       0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
                       0x56, 0x45, 0x56, 0x56, 0x56, 0x09, 0x09, 0x09 };
    int dataSize = 24;
    int compressedSize = byteCompress(dataPtr, dataSize);
    cout << compressedSize << endl;
    for (int i = 0; i < compressedSize; i++) {
        cout << hex << dataPtr[i];
    }
    cout << endl;
}
