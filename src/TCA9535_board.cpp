#include "TCA9535_board.h"

TCA9535_board::TCA9535_board() : TCA9535(0x20, "i2c-0")
{
	uint8_t data = LED1MASK | LED2MASK;
	openDev();
	configurateMask(port0, data, output);
	configurateMask(port1, data, output);
	ledOff(1);
	ledOff(2);
	ledOff(3);
}
TCA9535_board::~TCA9535_board() {}

bool TCA9535_board::parseData(int argc, char** argv)
{
	int opt;
	int8_t led = -1, red = -1, blue = -1, green = -1, off = -1;
	while((opt = getopt(argc, argv, ":l:r:b:g:o:L:R:B:G:O")) != -1)
	    {
	        switch(opt)
	        {
	        case 'l':
	        case 'L':
	        	if (strcmp(optarg, "led1") == 0)
	        		led = 1;
	        	else if (strcmp(optarg, "led2") == 0)
	        		led = 2;
	        	else if (strcmp(optarg, "led3") == 0)
	        		led = 3;
	        	break;
	        case 'r':
	        case 'R':
	        	red = atoi(optarg);
//	        	cout << "red value : " << red << endl;
	        	break;
	        case 'b':
	        case 'B':
	        	blue = atoi(optarg);
	        	break;
	        case 'g':
	        case 'G':
	        	green = atoi(optarg);
	        	break;
	        case 'o':
	        case 'O':
	        	off = atoi(optarg);
	        	break;
			case ':':
				cout << "option needs a value" << endl;
				break;
			case '?':
				cout << "unknown option: " << "optopt" << endl;
				break;
			default :
				break;
	        }
	    }

	if (led == -1)
	{
		cout << "please choose led " << endl;
		exit(1);
	}

	if (off == 0)
		ledOn(led);
	else if (off == 1)
		ledOff(led);

	turnLed(led, red, blue, green);
	cout << (int)led << endl;
	cout << (int) red << "---" << (int)blue << "---" << (int)green << endl;

	cout << (int)off << endl;

}

bool TCA9535_board::turnLed(uint8_t led, int8_t red, int8_t blue, int8_t green)
{
	uint8_t data;

	switch (led)
		{
		case 1:
			data = readPort(port0, output);
			if (red != -1)
				writeBit(port0, LED1RED, red);
			if (blue != -1)
				writeBit(port0, LED1BLUE, blue);
			if (green != -1)
				writeBit(port0, LED1GREEN, green);
			break;
		case 2:
			data = readPort(port0, output);
			if (red != -1)
				writeBit(port0, LED2RED, red);
			if (blue != -1)
				writeBit(port0, LED2BLUE, blue);
			if (green != -1)
				writeBit(port0, LED2GREEN, green);
			break;
		case 3:
			data = readPort(port1, output);
			if (red != -1)
				writeBit(port1, LED3RED, red);
			if (blue != -1)
				writeBit(port1, LED3BLUE, blue);
			if (green != -1)
				writeBit(port1, LED3GREEN, green);
			break;
		default:
			break;
		}
}

bool TCA9535_board::ledOn(uint8_t led)
{
	uint8_t data;

	switch (led)
	{
	case 1:
		data = readPort(port0, output);
		data |= LED1MASK;
		writePort(port0, data);
		break ;
	case 2:
		data = readPort(port0, output);
		data |= LED2MASK;
		writePort(port0, data);
		break ;
	case 3:
		data = readPort(port1, output);
		data |= LED3MASK;
		writePort(port1, data);
		break ;
	default :
		break;
	}

	return true;
}

bool TCA9535_board::ledOff(uint8_t led)
{
	uint8_t data;

	switch (led)
	{
	case 1:
		data = readPort(port0, output);
		data &= ~LED1MASK;
		writePort(port0, data);
		break ;
	case 2:
		data = readPort(port0, output);
		data &= ~LED2MASK;
		writePort(port0, data);
		break ;
	case 3:
		data = readPort(port1, output);
		data &= ~LED3MASK;
		writePort(port1, data);
		break ;
	default :
		break;
	}

	return true;
}
