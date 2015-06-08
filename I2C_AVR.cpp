#include "I2C_AVR.h"

void I2C_AVR::init(uint8_t addr) {
	this->m_address = addr;
	TWSR = 0;
	TWBR = ((8000000L/100000L)-16)/2;
}

uint8_t I2C_AVR::start() {
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));

	twi_status_register = TW_STATUS & 0xF8;
	if ((this->twi_status_register != TW_START) && (this->twi_status_register != TW_REP_START)) {
		return 1;
	}

	TWDR = m_address;
	TWCR = (1<<TWINT) | (1<<TWEN);

	while(!(TWCR & (1<<TWINT)));

	this->twi_status_register = TW_STATUS & 0xF8;
	if ((this->twi_status_register != TW_MT_SLA_ACK) && (this->twi_status_register != TW_MR_SLA_ACK)) {
		return 1;
	}
	return 0;
}

uint8_t I2C_AVR::write(uint8_t data) {
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);

	while(!(TWCR & (1<<TWINT)));

	this->twi_status_register = TW_STATUS & 0xF8;
	if (this->twi_status_register != TW_MT_DATA_ACK) {
		return 1;
		} else {
		return 0;
	}
}

void I2C_AVR::stop() {
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	while(TWCR & (1<<TWSTO));
}
