#include <repeated-byte-compression.hpp>

using namespace std;

int byteCompress(uint8_t *dataPtr[], int dataSize) {
    int compressedSize = 0;
    int i = 0;
    int j = 0;
    int dataLeft = dataSize;

    while (i < dataSize){
        uint8_t numRepeats = numberOfContigRepeats(&(*dataPtr)[i], dataLeft);
        if (numRepeats > 0) {
            (*dataPtr)[j] = (*dataPtr)[i] | (uint8_t) 0x80;
            // Store the amount of repetition
            (*dataPtr)[j+1] = numRepeats;
            compressedSize += 1;
            dataLeft -= numRepeats;
            // Update pre-compression index to skip repetitions
            // Update compression index to skip added repetition number
            i += numRepeats;
            j++;
        }

        else {
            (*dataPtr)[j] = (*dataPtr)[i];
        }

        compressedSize += 1;
        dataLeft--;
        i++;
        j++;
    }
    resizeArray(compressedSize, compressedSize, dataPtr);
    return compressedSize;
}

int byteDecompress(uint8_t *dataPtr[], int compressedSize) {
    int dataSize = 0;
    int j = 0;
    int tempSize = 2*compressedSize;
    uint8_t* tempDataPtr = new uint8_t[tempSize];

    for (int i = 0; i < compressedSize; i++) {

        if (checkRepeats((*dataPtr)[i])) {
            tempDataPtr[j] = (*dataPtr)[i] ^ (uint8_t) 0x80;
            uint8_t numRepeats = (*dataPtr)[i+1];
            insertRepeats(tempDataPtr[j], numRepeats, &tempDataPtr[j+1]);
            dataSize += numRepeats;
            i++;
            j+= numRepeats;
        }
        else {
            tempDataPtr[j] = (*dataPtr)[i];
        }
        j++;
        dataSize++;
        if (dataSize >= tempSize) {
            tempSize*=2*(dataSize/tempSize);
            resizeArray(tempSize, dataSize, &tempDataPtr);
        }
    }
    resizeArray(dataSize, dataSize, &tempDataPtr);
    *dataPtr = tempDataPtr;
    return dataSize;
}

int testFunction(uint8_t * dataPtr[], int dataSize) {
    uint8_t originalData[dataSize];
    memcpy(originalData, *dataPtr, dataSize);

    int compressedSize = byteCompress(dataPtr, dataSize);
    cout << dec << compressedSize << endl;
    for (int i = 0; i < compressedSize; i++) {
        cout << hex((*dataPtr)[i]);
    }
    cout << endl;

    int decompressedSize = byteDecompress(dataPtr, compressedSize);
    cout << dec << decompressedSize << endl;
    for (int i = 0; i < decompressedSize; i++) {
        cout << hex((*dataPtr)[i]);
    }
    cout << endl;

    assert (decompressedSize == dataSize);
    assert (equal(originalData, originalData + sizeof originalData / sizeof *originalData, *dataPtr));

    return EXIT_SUCCESS;
}

int randomTestGenerator(int numOfTests) {
    for (int i = 0; i < numOfTests; i++) {
        int randomSize = (rand() % 30) + 1;
        uint8_t testData[randomSize];
        int randomRepetition = (rand()%(randomSize/2));

        for (int j=0; j < randomSize; j++){
            uint8_t randomByte = (uint8_t)(rand() % 128);
            int k = 0;
            while (k < randomRepetition) {
                testData[j + k] = randomByte;
                k++;
            }
            j+=k-1;
        }

        uint8_t *testPtr = testData;
        testFunction(&testPtr, randomSize);
    }
    return EXIT_SUCCESS;
}

int main() {
    // Test compression on given array of data
    int dataSize = 24;
    uint8_t data[] = {0x03, 0x74, 0x04, 0x04, 0x04, 0x35, 0x35, 0x64,
                       0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
                       0x56, 0x45, 0x56, 0x56, 0x56, 0x09, 0x09, 0x09 };
    uint8_t *dataPtr = data;

    testFunction(&dataPtr, dataSize);

    // Further testing
    randomTestGenerator(5);


    return 0;

}

