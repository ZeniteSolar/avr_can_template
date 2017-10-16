# avr_can_template

PINOUT for the hardware board
---

~~
MCP2515 pin 12 =  INT (inverted)
atmega328p pin 4 = PD2, INT0, PCINT18

~~
MCP2515 pin 13 = SCK  
atmega328p pin 19 = PB5, PCINT5, SCK, arduino LED

~~
MCP2515 pin 14 = SI 
atmega328p pin 17 = PB3, PCINT3, PWM, MOSI

~~
MCP2515 pin 15 = SO 
atmega328p pin 18 = PB4, PCINT4, MISO

~~
MCP2515 pin 16 =  CS (inverted)
atmega328p pin 16 = PB2, OC1B, PCINT1, PWM

~~
MCP2515 pin 17 = RESET (inverted)
10kohm PULL-UP with a jumper

