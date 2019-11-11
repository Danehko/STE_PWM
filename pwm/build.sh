echo 'build v2.0 - Lucas'
if avr-g++ -Os *.cpp -mrelax -Wl,--gc-section -DF_CPU=16000000UL -mmcu=atmega328p -o pwm 
then
   avr-objcopy -O ihex -R .eeprom pwm pwm.hex
   avrdude -F -V -D -c avrispmkII -p ATMEGA2560 -P /dev/ttyUSB0 -b 115200 -U flash:w:pwm.hex
   rm pwm.hex
   rm pwm
fi
