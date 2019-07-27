# attiny402
Notes on programming an ATtiny402 on a Mac

## Setting up the build environment

Mac specific, my experience following https://github.com/vladbelous/tinyAVR_gcc_setup

### Install homebrew-avr
Assuming homebrew is installed and up to date:
```
$ brew tap osx-cross/avr
$ brew install avr-gcc
```
At the time of writing avr-gcc was at version 9.1.0, with partial support for avrxmega3 chips like the ATtiny402

### Hacking the missing bits
Download the latest AVR 8-bit toolchain, at the time of writing 3.6.2:

https://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en607660

and the latest ATtiny device support pack, at the time of writing 1.3.229, from

http://packs.download.atmel.com/

Extract and copy the following files

```
mkdir /usr/local/Cellar/avr-gcc/9.1.0/avr/lib/avrxmega3
cp avr8-gnu-toolchain-linux_x86_64/avr/lib/avrxmega3/short-calls/libc.a  /usr/local/Cellar/avr-gcc/9.1.0/avr/lib/avrxmega3/short-calls/
cp avr8-gnu-toolchain-linux_x86_64/avr/lib/avrxmega3/short-calls/libc.m  /usr/local/Cellar/avr-gcc/9.1.0/avr/lib/avrxmega3/short-calls/

cp Atmel.ATtiny_DFP.1.3.229/include/avr/iotn402.h /usr/local/Cellar/avr-gcc/9.1.0/avr/include/avr/
cp Atmel.ATtiny_DFP.1.3.229/gcc/dev/attiny402/avrxmega3/short-calls/crtattiny402.o /usr/local/Cellar/avr-gcc/9.1.0/avr/lib/avrxmega3/
cp Atmel.ATtiny_DFP.1.3.229/gcc/dev/attiny402/avrxmega3/short-calls/libattiny402.a /usr/local/Cellar/avr-gcc/9.1.0/avr/lib/avrxmega3/
```

Add an #elif for the ATtiny402 in io.h (/usr/local/Cellar/avr-gcc/9.1.0/avr/include/avr/io.h) in the long #if defined block:
```
#elif defined (__AVR_ATtiny402__)
#  include <avr/iotn402.h>
```

Rather than copy the device-spec from the device support pack, I copied the spec for the ATtiny412 and replaced every reference to a tiny412 to tiny402. This may or not be the correct thing to do.
```
cp /usr/local/Cellar/avr-gcc/9.1.0/lib/avr-gcc/9/gcc/avr/9.1.0/device-specs/specs-attiny412 /usr/local/Cellar/avr-gcc/9.1.0/lib/avr-gcc/9/gcc/avr/9.1.0/device-specs/specs-attiny402
```

And that should do it!

## Uploading to device

https://github.com/mraardvark/pyupdi

