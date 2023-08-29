all: blink.o
	avrdude -c usbasp-clone -p m328p -U flash:w:build/blink.hex

blink.o: src/blink.c 
	mkdir -pv build
	avr-gcc -mmcu=atmega328p -Wall -Os -o build/blink.elf src/blink.c
	avr-objcopy -j .text -j .data -O ihex build/blink.elf build/blink.hex

clean:
	rm -rf build 
