#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "irslinger.h"

int main(int argc, char *argv[])
{
	if (argc != 8)
	{
		printf("Usage: transmit [GPIO Broadcom Number] [Leading pulse duration (μs)] [Pulse duration] [Zero Gap duration] [One Gap duration] [Correction diver] [IR code binary]\n");
		exit(1);
	}

	double correction = atof(argv[6]); //measure the difference the real trnasmitted signal length and the expected length and decrares expected lenght with correctiond diver if needed

	uint32_t outPin = atoi(argv[1]);					  // The Broadcom pin number the signal will be sent on
	int leadingPulse = (int)(atoi(argv[2]) / correction); // The duration of the beginning pulse in microseconds
	int pulse = (int)(atoi(argv[3]) / correction);		  // The duration of a pulse in microseconds
	int zeroGap = (int)(atoi(argv[4]) / correction);	  // The duration of the gap in microseconds when sending a logical 0
	int oneGap = (int)(atoi(argv[5]) / correction);		  // The duration of the gap in microseconds when sending a logical 1

	int result = irSling(
		outPin,
		38000, // The frequency of the IR signal in Hz
		0.5,   // The duty cycle of the IR signal. 0.5 means for every cycle, the LED will turn on for half the cycle time, and off the other half
		leadingPulse,
		(int)leadingPulse / 2,
		pulse,
		pulse,
		oneGap,
		zeroGap,
		1, // 1 = Send a trailing pulse with duration equal to "onePulse", 0 = Don't send a trailing pulse
		argv[7]);

	return result;
}
