#ifndef _I2C_H_
#define _I2C_H_

#include <stdint.h>

class I2C {

public:
  virtual void init(uint8_t addr) = 0;
  virtual uint8_t start() = 0;
  virtual uint8_t write(uint8_t data) = 0;
  virtual void stop() = 0;
}
#endif
