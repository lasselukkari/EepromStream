#ifndef EepromStream_h
#define EepromStream_h

#include <Stream.h>

class EepromStream : public Stream {
public:
  EepromStream(int start, int size);

  void init();
  int available();
  int read();
  size_t write(uint8_t b);
  int peek();
  void flush();
  void rewind();

private:
    int _start;
    int _size;
    int _position;
    int _length;
};
#endif
