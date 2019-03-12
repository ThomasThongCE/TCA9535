/*
 * TCA9535_board.h
 *
 *  Created on: Mar 11, 2019
 *      Author: thomasthong
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include "TCA9535.h"

using namespace std;

#define LED1RED		1
#define LED1BLUE 	0
#define LED1GREEN	2

#define LED2RED		4
#define LED2BLUE	3
#define LED2GREEN	5

#define LED3RED		1
#define LED3BLUE	0
#define LED3GREEN	2

#define LED1MASK	0x07
#define LED2MASK	0x38
#define LED3MASK	0x07

class TCA9535_board : public TCA9535
{
private:
	//uint8_t const LED1MASK = 0x07, LED2MASK = 0x38, LED3MASK = 0x07;
public:
	TCA9535_board();
	~TCA9535_board();

	bool parseData(int argc, char **argv) ;

	bool turnLed(uint8_t led, int8_t red = -1, int8_t blue = -1, int8_t green = -1);
	bool ledOn(uint8_t led);
	bool ledOff(uint8_t led);
};


