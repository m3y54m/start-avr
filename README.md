# Getting started with AVR programming

Target microcontroller: Atmega328P

Host OS: Ubuntu 20.04 (Running on Windows WSL2)

## Install AVR-GCC Compiler

```console
sudo apt-get install gcc build-essential
sudo apt-get install gcc-avr binutils-avr avr-libc gdb-avr
```

## Install AVRDUDE

Install In-system programming software avrdude. AVRDUDE is an open source utility to download/upload/manipulate the ROM and EEPROM contents of AVR microcontrollers using the in-system programming technique (ISP).

```console
sudo apt-get install libusb-dev
sudo apt-get install avrdude
```

## Atmega328P Pinout

![68747470733a2f2f692e696d6775722e636f6d2f715849456368542e6a7067](https://github.com/m3y54m/start-avr-linux/assets/1549028/5b1a40e6-b7c9-4ace-acd8-75e5bdb56ed6)

## The `blink.c` Program

```c
// Default clock source is internal 8MHz RC oscillator
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRB |= (1 << PB0);

	while (1)
	{
		PORTB |= (1 << PB0);
		_delay_ms(1000);
		PORTB &= ~(1 << PB0);
		_delay_ms(1000);
	}
	return 0;
}
```

## Programmer

- [USBasp - USB programmer for Atmel AVR controllers](https://www.fischl.de/usbasp/)

![image](https://github.com/m3y54m/start-avr-linux/assets/1549028/274377b5-8b9a-4aef-9fb1-94cd0eedecb7)

### ISP Programmer Pinout

![image](https://github.com/m3y54m/start-avr-linux/assets/1549028/f80fc5cf-42a9-4e41-b1bc-518537fea0dd)

### Connection

![USBASP-10-pin-wiring-to-AVR-Atmega328-chip](https://github.com/m3y54m/start-avr-linux/assets/1549028/62c4d115-8f2d-4aba-bbb1-6028d10de6b0)

## Build the Program


```console
avr-gcc -mmcu=atmega328p -Wall -Os -o build/blink.elf src/blink.c
avr-objcopy -j .text -j .data -O ihex build/blink.elf build/blink.hex
```

## Upload the Program to Atmega328P

To ensure that the USBasp programmer is detected and connected to Atmega328, verify the device signature:

```console
avrdude -c usbasp-clone -p m328p
```

Upload the program:

```console
avrdude -c usbasp-clone -p m328p -U flash:w:build/blink.hex
```

## Resources

- [ATmega48A/PA/88A/PA/168A/PA/328/P Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf)
- [AVR Programing Using avrdude in Ubuntu](https://medium.com/@ppatil/avr-programing-using-avrdude-in-ubuntu-93734c26ad19)
- [A simple LED blinking project that uses the AVR toolchain without the Arduino IDE. ](https://github.com/tzhenghao/blink-ATmega328p)
- [Standalone ATmega328p](https://doc.riot-os.org/group__boards__atmega328p.html)
- [How to Program an AVR chip using a USBASP](http://www.learningaboutelectronics.com/Articles/Program-AVR-chip-using-a-USBASP-with-10-pin-cable.php)
- [Programing AVR on Ubuntu with USBasp for beginers](https://fos.cmb.ac.lk/esl/programing-avr-ubuntu-14-04-usbasp/)
- [AVRDUDE - AVR Downloader/UploaDEr](https://www.nongnu.org/avrdude/)
- [AVRDUDESS: A GUI for AVRDUDE](https://github.com/ZakKemble/AVRDUDESS)
- [AVR® Fuse Calculator](https://www.engbedded.com/fusecalc/)
- [Attach a USB device to WSL](https://learn.microsoft.com/en-us/windows/wsl/connect-usb)
