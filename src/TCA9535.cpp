/*
 * TCA9535.cpp
 *
 *  Created on: Mar 7, 2019
 *      Author: thomasthong
 */

#include "TCA9535.h"

TCA9535::TCA9535(int addr, string port) : address(addr)
{
	this->port = "/dev/" + port;
	cout << "init at " << this->port << endl;
}

TCA9535::~TCA9535()
{
	//close i2c device
	closeDev();
}

bool TCA9535::openDev()
{
	if ((fd = open(port.c_str(), O_RDWR)) < 0)
	{
		cout << "Couldn't open i2c port" << endl;
		exit(1);
	}

	if (ioctl(fd,I2C_SLAVE,address) < 0)
	{
		cout << "Failed when set slave address for i2c port" << endl;
		exit(1);
	}
}

bool TCA9535::closeDev()
{
	if (close(fd) < 0)
		cout << "can't close i2c port" << endl;
}

bool TCA9535::writeRegister(uint8_t command, uint8_t data)
{
	uint8_t buff[2];
	buff[0] = command;
	buff[1] = data;

	if (write(fd,buff,2) != 2)
	{
		/* ERROR HANDLING: i2c transaction failed */
		cout << "Failed to write to the i2c bus" << endl;
		cout << "errno " << errno << " : " << strerror(errno) << endl;
		cout << endl ;
		exit(1);
	}

}

uint8_t TCA9535::readRegister(uint8_t command)
{
	uint8_t data;

	if (write(fd,&command,1) != 1)
	{
		/* ERROR HANDLING: i2c transaction failed */
		cout << "Failed to read to the i2c bus" << endl;
		cout << "errno " << errno << " : " << strerror(errno) << endl;
		cout << endl;
		exit(1);
	}

	if (read(fd,&data,1) != 1)
	{
		/* ERROR HANDLING: i2c transaction failed */
		cout << "Failed to read from the i2c bus." << endl;
		cout << "errno [" << errno << "] : " << strerror(errno) << endl;
		cout << endl ;
		exit(1);
	}

	return data;
}

bool TCA9535::configuratePort(Port port, Function function)
{
	uint8_t addr;
	if (port == port0)
		addr = CONFIGUREPORT0;
	else if (port == port1)
		addr = CONFIGUREPORT1;
	else
	{
		cout << "port input error." << endl;
		return false;
	}

	if (function == input)
	{
		writeRegister(addr, 0xff);
	}
	else if (function == output)
	{
		writeRegister(addr, 0x00);
	}
	return true;
}

bool TCA9535::configurateBit(Port port, uint8_t bit, Function function)
{
	uint8_t addr, data;
	if (port == port0)
		addr = CONFIGUREPORT0;
	else if (port == port1)
		addr = CONFIGUREPORT1;
	else
	{
		cout << "port input error." << endl;
		return false;
	}

	data = readRegister(addr);
	// using ceec set bit
	if (function == input)
		{
			data |= 1 << bit;
		}
		else if (function == output)
		{
			data &= ~(1 << bit);
		}

	writeRegister(addr, data);
	return true;
}


bool TCA9535::writePort(Port port, uint8_t data)
{
	uint8_t addr;
	if (port == port0)
		addr = OUTPORT0;
	else if (port == port1)
		addr = OUTPORT1;
	else
	{
		cout << "port input error." << endl;
		return false;
	}

	writeRegister(addr, data);
	return true;
}

bool TCA9535::writeBit(Port port,uint8_t bit, bool value)
{
	uint8_t addr, data;
	if (port == port0)
		addr = OUTPORT0;
	else if (port == port1)
		addr = OUTPORT1;
	else
	{
		cout << "port input error." << endl;
		return false;
	}

	data = readRegister(addr);

	if (value)
		data |= 1 << bit;
	else data &= ~(1 << bit);
	writeRegister(addr, data);

	 return true;
}


uint8_t TCA9535::readPort(Port port)
{
	uint8_t addr;
	if (port == port0)
		addr = INPUTPORT0;
	else if (port == port1)
		addr = INPUTPORT1;
	else
	{
		cout << "port input error." << endl;
		return false;
	}

	return readRegister(addr);
}

bool TCA9535::readBit(Port port, uint8_t bit)
{
	return (readPort(port) & (1 << bit));
}


uint8_t TCA9535::invertPort(Port port, uint8_t data)
{
	uint8_t addr;
	if (port == port0)
		addr = INVPORT0;
	else if (port == port1)
		addr = INVPORT1;
	else
	{
		cout << "port input error." << endl;
		return false;
	}

	writeRegister(addr, data);
	return true;
}

bool TCA9535::invertBit(Port port, uint8_t bit, bool value)
{
	uint8_t addr, data;
	if (port == port0)
		addr = INVPORT0;
	else if (port == port1)
		addr = INVPORT1;
	else
	{
		cout << "port input error." << endl;
		return false;
	}

	data = readRegister(addr);

	if (value)
		data |= 1 << bit;
	else data &= ~(1 << bit);

	writeRegister(addr, data);
	return true;
}
