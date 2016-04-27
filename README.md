IR Slinger
==========

[![Build Status](https://travis-ci.org/bschwind/ir-slinger.svg?branch=travis)](https://travis-ci.org/bschwind/ir-slinger)

Small C library for sending NEC-like infrared packets on the Raspberry Pi
This is a header-only library. Use it by including "irslinger.h" and
linking to libmath, pigpio, and pthread (-lm -lpigpio -pthread)

Dependencies
------------

* [libpigpio](https://github.com/joan2937/pigpio)
  * git clone https://github.com/joan2937/pigpio.git
  * cd pigpio
  * make
  * sudo make install

Build
-----

    gcc test.c -lm -lpigpio -pthread

Or

    clang test.c -lm -lpigpio -pthread

Usage
-----

```
#include <stdio.h>
#include "irslinger.h"

int main(int argc, char *argv[])
{
  uint32_t outPin = 23;            // The Broadcom pin number the signal will be sent on
  int frequency = 38000;           // The frequency of the IR signal in Hz
  double dutyCycle = 0.5;          // The duty cycle of the IR signal. 0.5 means for every cycle,
                                   // the LED will turn on for half the cycle time, and off the other half
  int leadingPulseDuration = 9000; // The duration of the beginning NEC pulse in microseconds
  int leadingGapDuration = 4500;   // The duration of the gap in microseconds after the leading NEC pulse
  int onePulse = 562;              // The duration of a pulse in microseconds when sending a logical 1
  int zeroPulse = 562;             // The duration of a pulse in microseconds when sending a logical 0
  int oneGap = 1688;               // The duration of the gap in microseconds when sending a logical 1
  int zeroGap = 562;               // The duration of the gap in microseconds when sending a logical 0
  int sendTrailingPulse = 1;       // 1 = Send a trailing pulse with duration equal to "onePulse"
                                   // 0 = Don't send a trailing pulse

  int result = irSling(
    outPin,
    frequency,
    dutyCycle,
    leadingPulseDuration,
    leadingGapDuration,
    onePulse,
    zeroPulse,
    oneGap,
    zeroGap,
    sendTrailingPulse,
    "01000001101101100101100010100111");
  
  return result;
}
```

GPIO Pin info from the pigpio repo:
-----------------------------------

ALL gpios are identified by their Broadcom number.  See elinux.org

There are 54 gpios in total, arranged in two banks.

Bank 1 contains gpios 0-31.  Bank 2 contains gpios 32-54.

A user should only manipulate gpios in bank 1.

There are at least three types of board.

Type 1

    26 pin header (P1).

    Hardware revision numbers of 2 and 3.

    User gpios 0-1, 4, 7-11, 14-15, 17-18, 21-25.

Type 2

    26 pin header (P1) and an additional 8 pin header (P5).

    Hardware revision numbers of 4, 5, 6, and 15.

    User gpios 2-4, 7-11, 14-15, 17-18, 22-25, 27-31.

Type 3

    40 pin expansion header (J8).

    Hardware revision numbers of 16 or greater.

    User gpios 2-27 (0 and 1 are reserved).
