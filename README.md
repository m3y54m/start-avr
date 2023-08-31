# Getting started with AVR programming

If you want to start AVR programming and you don't know how, this repository is created for you.

There are two great resources to learn AVR programming which I highly recommend them to beginners:

- [🎞️ Getting Started With AVR](https://www.youtube.com/playlist?list=PLtQdQmNK_0DRhBWYZ32BEILOykXLpJ8tP)
- [📕 Make: AVR Programming - Elliot Williams](https://www.oreilly.com/library/view/make-avr-programming/9781449356484/)
- [Code examples for the book "Make: AVR Programming"](https://github.com/hexagon5un/AVR-Programming)

For this project I use Atmega328P which is a very famous and lovely microcontroller used in Arduino Uno.
Keep in mind that we are not using Arduino IDE or Arduino Core here. We are going to learn and practice AVR bare-metal programming.

**If you want to use other AVR microcontrollers, you should change the [`Makefile`](Makefile)**.

[AVR-GCC](https://gcc.gnu.org/wiki/avr-gcc) is the most popular toolchain for AVR programming. I recommend you to use Linux to install AVR-GCC to compile and build AVR programs. It is easier and you will have less problems. However, Windows users can use WSL or VirtualBox to virtualize Linux. If you don't want to use Linux at all, you can use the [pre-built AVR-GCC toolchain for Windows presented by Microchip](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers).

- Target microcontroller: **Atmega328P**
- Host OS: **Ubuntu 20.04 (Running on Windows WSL2)**

## Install AVR-GCC Compiler

Ubuntu users:

```console
sudo apt-get install gcc build-essential
sudo apt-get install gcc-avr binutils-avr avr-libc gdb-avr
```

Windows users:

Download and extract [AVR 8-Bit Toolchain (Windows)](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers). Add the address of `bin` folder to your system `Path`.

- [Using the GNU AVR toolchain on Windows 10](http://fab.cba.mit.edu/classes/863.16/doc/projects/ftsmin/windows_avr.html#avr-gcc)
- [AVR GCC Toolchain – Setup for Windows](https://tinusaur.com/guides/avr-gcc-toolchain/)
- [Make for Windows](https://gnuwin32.sourceforge.net/packages/make.htm)

## Install AVRDUDE

Install In-system programming software avrdude. AVRDUDE is an open source utility to download/upload/manipulate the ROM and EEPROM contents of AVR microcontrollers using the in-system programming technique (ISP).

Ubuntu users:

```console
sudo apt-get install libusb-dev
sudo apt-get install avrdude
```

Windows users:

Download and extract [AVRDUDE for Windows](https://github.com/avrdudes/avrdude/releases). Add the address of the folder to your system `Path`.

There is also a GUI version of AVRDUDE for Windows called [AVRDUDESS](https://github.com/ZakKemble/AVRDUDESS) which can be used to program your microcontroller manually.

## Atmega328P Pinout

![Atmega328P Pinout](https://github.com/m3y54m/start-avr/assets/1549028/7c222c32-0c19-44ef-be49-052d2cd0fc68)

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

> Wait! If you have an AVR based Arduino board (Uno, Nano, etc.), you do not need a programmer! 😀
>
> [Go to Arduino section](#arduino)

- [USBasp - USB programmer for Atmel AVR controllers](https://www.fischl.de/usbasp/)

![USBasp](https://github.com/m3y54m/start-avr/assets/1549028/0ef402de-c759-4e85-b45b-a7d1f495e17c)

### ISP Pinout

![ISP Pinout](https://github.com/m3y54m/start-avr/assets/1549028/017c2d6d-ee3a-41b0-8b64-752e97a389b2)

### Programmer Connection

![Programmer Connection](https://github.com/m3y54m/start-avr/assets/1549028/0efd9b1c-5292-42c6-a5ec-60286b23cdf9)

### LED Blinky Circuit

![LED Blinky Circuit](https://github.com/m3y54m/start-avr/assets/1549028/c2ffe75c-f015-48a5-b35e-3d77a0dabc1d)

## Build the Program

```console
avr-gcc -mmcu=atmega328p -Wall -Os -o build/blink.elf src/blink.c
avr-objcopy -j .text -j .data -O ihex build/blink.elf build/blink.hex
```

or just use the `Makefile` and execute this command:

```console
make
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

or just use the `Makefile` and execute this command:

```console
make upload
```

**⚠️ WARNING:**

**Do not play with *FUSE BITS*** if you do not know what you are doing!

Fuse bits can be used to change clock source of the microcontroller and enable / disable some of its functionalities.
If you do something wrong with the fuse bits you may brick your microcontroller. So read these articles before manipulating them:

- [Fuse bits aren’t that scary](https://embedderslife.wordpress.com/2012/08/20/fuse-bits-arent-that-scary/)
- [AVR® Fuses](https://microchipdeveloper.com/8avr:avrfuses)

## Arduino

The AVR microcontroller on an Arduino board simply can be programmed by AVRDUDE without the need of any external programmer. The Arduino bootloader makes this possible.

For example if you want to program an Arduino Uno (with Atmega328P on it) use this command:

```console
avrdude -c arduino -p m328p -P COM10 -b 115200 -U flash:w:build/blink.hex
```
`COMx` is the Arduino boards's serial port name in Windows. In Linux it should be something like `/dev/ttyxxxx`

Note that for Arduino Uno you should set `F_CPU` to `16000000UL`.

For more information read this article:

- [Introduction to Bare Metal Programming in Arduino Uno](https://www.hackster.io/milanistef/introduction-to-bare-metal-programming-in-arduino-uno-f3e2b4)

## My AVR Playground

I have a playground repository for AVR programming where I rewrite my old AVR programs and practice my fundamental embedded programming skills. It could be beneficial for you as well:

- [My AVR Programming Playground](https://github.com/m3y54m/avr-playground)

## Resources

- [ATmega48A/PA/88A/PA/168A/PA/328/P Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf)
- [AVR Programing Using avrdude in Ubuntu](https://medium.com/@ppatil/avr-programing-using-avrdude-in-ubuntu-93734c26ad19)
- [A simple LED blinking project that uses the AVR toolchain without the Arduino IDE.](https://github.com/tzhenghao/blink-ATmega328p)
- [How to Build an AVR Blinking LED Circuit](http://www.learningaboutelectronics.com/Articles/AVR-blinking-LED-circuit.php)
- [Standalone ATmega328p](https://doc.riot-os.org/group__boards__atmega328p.html)
- [How to Program an AVR chip using a USBASP](http://www.learningaboutelectronics.com/Articles/Program-AVR-chip-using-a-USBASP-with-10-pin-cable.php)
- [Programing AVR on Ubuntu with USBasp for beginers](https://fos.cmb.ac.lk/esl/programing-avr-ubuntu-14-04-usbasp/)
- [AVR-GCC](https://gcc.gnu.org/wiki/avr-gcc)
- [AVRDUDE - AVR Downloader/UploaDEr](https://github.com/avrdudes/avrdude)
- [AVRDUDESS: A GUI for AVRDUDE](https://github.com/ZakKemble/AVRDUDESS)
- [AVR® Fuse Calculator](https://www.engbedded.com/fusecalc/)
- [Attach a USB device to WSL](https://learn.microsoft.com/en-us/windows/wsl/connect-usb)
