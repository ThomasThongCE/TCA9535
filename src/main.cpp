/** @mainpage TCA9535 - None
 *
 * @author anonymous <anony@mo.us>
 * @version 1.0.0
**/


#include <stdio.h>
#include "TCA9535.h"
#include "TCA9535_board.h"
/**
 * Main class of project TCA9535
 *
 * @param argc the number of arguments
 * @param argv the arguments from the commandline
 * @returns exit code of the application
 */
int main(int argc, char **argv) {
	// print a greeting to the console
	printf("Hello World!\n");

//	TCA9535 test(0x20, "i2c-0");
//	test.openDev();
//	test.configuratePort(port1, output);
//	test.configuratePort(port0, input);
//	test.writePort(port1, 0xff);
//	test.invertPort(port0, 0x00);
//	cout << (int)test.readPort(port0, input) << endl;

	cout << "number of argument : " << argc << endl;

	TCA9535_board test2;
	test2.parseData(argc, argv);

	printf("Finish\n");

	return 0;
}
