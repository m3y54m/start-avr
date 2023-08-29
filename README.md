# Getting started with AVR programming in Linux

## Prepare Build Environment

```console
sudo apt install gcc build-essential
sudo apt install gcc-avr binutils-avr avr-libc gdb-avr
```

## Atmega328P Pinout

![68747470733a2f2f692e696d6775722e636f6d2f715849456368542e6a7067](https://github.com/m3y54m/start-avr-linux/assets/1549028/5b1a40e6-b7c9-4ace-acd8-75e5bdb56ed6)

## Programmer

- [USBasp - USB programmer for Atmel AVR controllers](https://www.fischl.de/usbasp/)

![image](https://github.com/m3y54m/start-avr-linux/assets/1549028/274377b5-8b9a-4aef-9fb1-94cd0eedecb7)

### ISP Programmer Pinout

![image](https://github.com/m3y54m/start-avr-linux/assets/1549028/f80fc5cf-42a9-4e41-b1bc-518537fea0dd)

### Connection

![USBASP-10-pin-wiring-to-AVR-Atmega328-chip](https://github.com/m3y54m/start-avr-linux/assets/1549028/62c4d115-8f2d-4aba-bbb1-6028d10de6b0)

## Upload the Program to Atmega328P

Verify reading device signature. Use following command

```console
$sudo avrdude -c usbasp-clone -p m328p
```

## Resources

- [ATmega48A/PA/88A/PA/168A/PA/328/P Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf)
- [AVR Programing Using avrdude in Ubuntu](https://medium.com/@ppatil/avr-programing-using-avrdude-in-ubuntu-93734c26ad19)
- [Standalone ATmega328p](https://doc.riot-os.org/group__boards__atmega328p.html)
- [How to Program an AVR chip using a USBASP](http://www.learningaboutelectronics.com/Articles/Program-AVR-chip-using-a-USBASP-with-10-pin-cable.php)
- [AVRDUDE - AVR Downloader/UploaDEr](https://www.nongnu.org/avrdude/)
- [AVRDUDESS: A GUI for AVRDUDE](https://github.com/ZakKemble/AVRDUDESS)
