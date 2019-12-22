F8:59:71:3E:FE:3A

Ekkels Laptop BT address
AT+INIT
AT+PSWD=0000
AT+PAIR=f859,71,3efe3a,20
AT+BIND=f859,71,3efe3a
AT+RMAAD
AT+LINK=f859,71,3efe3a

AT+FSAD=f859,71,3efe3a


telefoon
3074,96,6A9C27
Anke's foon
CC9F,7A,21F6AE

AT
AT+ORGL


20:19:09:26:03:28

20:19:92:60:328


werklaptop

1856,80,2D008B

ankes Laptop

646E,69,EB0DFA
connect to terminal


https://roboindia.com/tutorials/arduino-hc-05-at-mode/

https://arduino.stackexchange.com/questions/16954/problems-connecting-reliably-using-hc-05-as-bluetooth-masterAT



AT+RESET
AT+ORGL (Set to original)
AT+NAME=ODBRDR
AT+ROLE=1 (Set to Master)
AT+CMODE=0 (Set connect to a specific address)
AT+PSWD=0000
AT+BIND=f859,71,3efe3a
AT+INIT (Need to connect)
AT+PAIR=f859,71,3efe3a,20 (,20 means 20 second timeout)
AT+LINK=f859,71,3efe3a



http://www.userk.co.uk/arduino-bluetooth-linux/

open spp channels bluetooth
sdptool add --channel=22 SP
rfcomm listen /dev/rfcomm0 22
