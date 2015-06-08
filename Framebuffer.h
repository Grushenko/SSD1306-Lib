#include <stdint.h>
#include "SSD1306.h"

class Framebuffer {
	private:
		uint8_t m_width;
		uint8_t m_height;
		
		uint16_t m_buffersize;
		uint8_t* m_buffer;
		SSD1306 m_display;
	
	public:
		Framebuffer(I2C* i2c, uint8_t addr, uint8_t width, uint8_t height);
		//    void drawBitmap(const uint8_t *bitmap, uint8_t height, uint8_t width, uint8_t pos_x, uint8_t pos_y);
		//    void drawBuffer(const uint8_t *buffer);
		void drawPixel(uint8_t pos_x, uint8_t pos_y, uint8_t pixel_status);
		void drawPixel(uint8_t pos_x, uint8_t pos_y);
		void drawVLine(uint8_t x, uint8_t y, uint8_t length);
		void drawHLine(uint8_t pos_y, uint8_t start, uint8_t length);
		void drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
		void drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fill);
		void invert(uint8_t status);
		void clear();
		void show();
};
