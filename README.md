# avr_can_template
This is a template for starting a canbus using multiples atmega328p + MCP2515.

To use it:
```
git clone --recursive http://github.com/zeniteSolar/avr_can_template
cd avr_can_template
./make_libs_all.sh      # make libs
./make_all.sh           # make firmware0 and firmware1
./up_all.sh             # make and upload to ACM0 and ACM1 using avrdude
```

PINOUT for the hardware board
---

```
MCP2515 pin 12    =   INT (inverted)
atmega328p pin 4  =   PD2, INT0, PCINT18
```
```
MCP2515 pin 13    =   SCK  
atmega328p pin 19 =   PB5, PCINT5, SCK, arduino LED
```
```
MCP2515 pin 14    =   SI 
atmega328p pin 17 =   PB3, PCINT3, PWM, MOSI
```
```
MCP2515 pin 15    =   SO 
atmega328p pin 18 =   PB4, PCINT4, MISO
```
```
MCP2515 pin 16    =   CS (inverted)
atmega328p pin 16 =   PB2, OC1B, PCINT1, PWM
```
```
MCP2515 pin 17    = RESET (inverted)
10kohm PULL-UP with a jumper
```
