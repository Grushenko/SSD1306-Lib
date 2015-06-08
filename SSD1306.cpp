#include <stdint.h>

#include "SSD1306.h"

SSD1306::SSD1306(I2C* i2c, uint8_t addr, uint8_t width, uint8_t height) {

    m_i2c = i2c;

    m_width = width;
    m_height = height;
    m_buffersize = (width*height)/8;

    (*m_i2c).init(addr);

    // Turn display off
    sendCommand(SSD1306_DISPLAYOFF);

    sendCommand(SSD1306_SETDISPLAYCLOCKDIV);
    sendCommand(0x80);

    sendCommand(SSD1306_SETMULTIPLEX);
    sendCommand(0x3F);

    sendCommand(SSD1306_SETDISPLAYOFFSET);
    sendCommand(0x00);

    sendCommand(SSD1306_SETSTARTLINE | 0x00);

    // We use internal charge pump
    sendCommand(SSD1306_CHARGEPUMP);
    sendCommand(0x14);

    // Horizontal memory mode
    sendCommand(SSD1306_MEMORYMODE);
    sendCommand(0x00);

    sendCommand(SSD1306_SEGREMAP | 0x1);

    sendCommand(SSD1306_COMSCANDEC);

    sendCommand(SSD1306_SETCOMPINS);
    sendCommand(0x12);

    // Max contrast
    sendCommand(SSD1306_SETCONTRAST);
    sendCommand(0xCF);

    sendCommand(SSD1306_SETPRECHARGE);
    sendCommand(0xF1);

    sendCommand(SSD1306_SETVCOMDETECT);
    sendCommand(0x40);

    sendCommand(SSD1306_DISPLAYALLON_RESUME);

    // Non-inverted display
    sendCommand(SSD1306_NORMALDISPLAY);

    // Turn display back on
    sendCommand(SSD1306_DISPLAYON);
}

void SSD1306::sendCommand(uint8_t command) {
  (*m_i2c).start();
  (*m_i2c).write(0x00);
  (*m_i2c).write(command);
  (*m_i2c).stop();
}

void SSD1306::invert(uint8_t inverted) {
    if (inverted) {
        sendCommand(SSD1306_INVERTDISPLAY);
    } else {
        sendCommand(SSD1306_NORMALDISPLAY);
    }
}

void SSD1306::sendFramebuffer(uint8_t *buffer) {
    sendCommand(SSD1306_COLUMNADDR);
    sendCommand(0x00);
    sendCommand(0x7F);

    sendCommand(SSD1306_PAGEADDR);
    sendCommand(0x00);
    sendCommand(0x07);

    // We have to send the buffer as 16 bytes packets
    // Our buffer is m_buffersize bytes long
    // We have to send m_buffersize/16 packets
    for (uint8_t packet = 0; packet < m_buffersize/16; packet++) {
      (*m_i2c).start();
      (*m_i2c).write(0x40);
        for (uint8_t packet_byte = 0; packet_byte < 16; ++packet_byte) {
          (*m_i2c).write(buffer[packet*16+packet_byte]);
        }
        (*m_i2c).stop();
    }
}
