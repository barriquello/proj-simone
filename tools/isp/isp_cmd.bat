SET CURRENTDIR="%cd%"

"C:\Arduino\hardware\tools\avr\bin\avrdude.exe" -CC:\Arduino\hardware\tools\avr/etc/avrdude.conf -v -patmega2560 -cwiring -PCOM46 -b115200 -D -Uflash:w:"brtos_atmega2560.hex":i