Current meter: *Sagecom T211-D*

2 ports:
* P1: Slow data | 1/s
* S1: Raw data  | 4000/s 

Cable adapter: 

| PIN | SIGNAAL   | BESCHRIJVING                     |
|-----|-----------|----------------------------------|
| 1   | +5V       | Voltage adapter measure stuff    |
| 2   | RTS       | Input                            |
| 3   | GND       | Data ground                      |
| 4   | –         | –                                |
| 6   | RX        | Output                           |
| 6   | Power GND | Ground for adapter measure stuff |


Packets get send over serial port in linux this would be something like */dev/ttyUSB0*

We have  to take into account several different 


https://www.netbeheernederland.nl/_upload/Files/Slimme_meter_15_a727fce1f1.pdf

Page 15 contains telegram layout thing