make clean all
fuser -k /dev/ttyACM1
avrdude -c arduino -P /dev/ttyACM1 -p m328p -D -U flash:w:bin/firmware1.elf
