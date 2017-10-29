# repeated-byte-compression
Algorithm that will compress a given data buffer of bytes.

### Assumptions:
1. The data_ptr will point to an array of bytes.  Each byte will contain a number from 0 to 127 (0x00 to 0x7F).  It is common for the data in the buffer to have the same value repeated in the series.
2. The compressed data will need to be decompressable.  Please ensure that your algorithm allows for a decompression algorithm to return the buffer to it’s previous form.

### Example data and function call:
Data before the call:

dataPtr[] = { 0x03, 0x74, 0x04, 0x04, 0x04, 0x35, 0x35, 0x64,
            0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x56, 0x45, 0x56, 0x56, 0x56, 0x09, 0x09, 0x09 };
             
dataSize = 24;

newSize = byte_compress( data_ptr, data_size );
