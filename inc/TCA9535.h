/*
 * TCA9535.h
 *
 *  Created on: Mar 7, 2019
 *      Author: thomasthong
 */

#ifndef TCA9535_H_
#define TCA9535_H_

#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>		// For O_RDWR
#include <unistd.h>		// For open(), create(), close()
#include <sys/ioctl.h>  // For ioctl()
#include <linux/i2c-dev.h> 	// For I2C_SLAVE

#include <cerrno>


//#define ADDRESS 0x20

// TCA9535 Command address
#define INPUTPORT0 0x00
#define INPUTPORT1 0x01
#define OUTPORT0 0x02
#define OUTPORT1 0x03
#define INVPORT0 0x04
#define INVPORT1 0x05
#define CONFIGUREPORT0 0x06
#define CONFIGUREPORT1 0x07

using namespace std;

enum Port {port0, port1};
enum Function {input, output};

class TCA9535
{
private:
	int address;
	string port;
	int fd;

	bool writeRegister(uint8_t command, uint8_t data);
	uint8_t readRegister(uint8_t command);

public:
	TCA9535(int addr, string port);
	~TCA9535();

	bool openDev();	// open i2c port
	bool closeDev();	// close i2c port

	bool configuratePort(Port port, Function function);
	bool configurateBit(Port port, uint8_t bit, Function function);
	bool configurateMask(Port port, uint8_t mask, Function function);

	uint8_t readPort(Port port, Function function);								// return port value
	bool readBit(Port port, Function function, uint8_t bit);					// return value of that bit

	bool writePort(Port port, uint8_t data);					// return whether if success or not
	bool writeBit(Port port, uint8_t bit, bool value);	// return whether if success or not

	uint8_t invertPort(Port port, uint8_t data);							// return value of the invert port
	bool invertBit(Port port, uint8_t bit, bool value);					// return value of the invertbit
};

//helper function




#endif /* TCA9535_H_ */
