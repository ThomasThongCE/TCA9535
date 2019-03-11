/** @mainpage TCA9535 - None
 *
 * @author anonymous <anony@mo.us>
 * @version 1.0.0
**/


#include <stdio.h>
#include "TCA9535.h"
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

	TCA9535 test(0x20, "i2c-0");
	test.openDev();

	printf("Finish\n");

	return 0;
}
