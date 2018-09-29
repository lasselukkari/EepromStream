#include "Arduino.h"
#include <EEPROM.h>
#include "EepromStream.h"

EepromStream::EepromStream(int start, int size):
  _size(size-2),
  _start(start+2),
  _position(0){
}

void EepromStream::init(){
  _length = EEPROM.read(_start-2) | EEPROM.read(_start-1) << 8;
}

int EepromStream::available(){
    return _length - _position;
}


int EepromStream::read(){
  if (available()){
      return EEPROM.read(_start + _position++);
  } else {
    return -1;
  }
}

size_t EepromStream::write(uint8_t b){
  if (_position < _size){
    EEPROM.write(_start +_position++, b);
    return 1;
  } else {
    return 0;
  }
}

int EepromStream::peek(){
  if (available()){
    return EEPROM.read(_start + _position + 1);
  } else {
    return -1;
  }
}

void EepromStream::flush(){
  EEPROM.write(_start-2, _position & 0xFF);
  EEPROM.write(_start-1, (_position >> 8) & 0xFF);
#ifdef ESP8266
  EEPROM.commit();
#endif
  _length = _position;
  _position = 0;
}

void EepromStream::rewind(){
  _position = 0;
}
