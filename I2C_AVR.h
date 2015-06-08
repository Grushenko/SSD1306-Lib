#ifndef __I2C_AVR_H__
#define __I2C_AVR_H__
#include "I2C.h"

class I2C_AVR {
public:
  void init(uint8_t addr);
  uint8_t start();
  uint8_t write(uint8_t data);
  void stop();
private:
  uint8_t m_address;
  uint8_t twi_status_register;
}

#endif
